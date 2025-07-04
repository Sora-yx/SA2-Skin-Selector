#include "pch.h"
#include "menu.h"

bool DeleteHomingAttackEffect = false;
bool deleteEyeTracker[PMax] = { false };

TaskHook EyeTracker_t(0x4766C0);
UsercallFuncVoid(DoHomingAttackEffect_t,
	(SonicCharObj2* sco2, EntityData1* twp, EntityData2* mwp, CharObj2Base* co2), (sco2, twp, mwp, co2), 0x720E00, rEBX, stack4, stack4, stack4);

TaskHook HomingDashAuraDisp_t(0x757040);
TaskHook CameraMain_t(cameraCons_Main);
FunctionHook<void, int> RunObjectIndex_t(RunObjectIndex);
TaskHook LastBossPlayerManager_t(LastBossPlayerManager);

bool reloadSound = false;

FunctionHook<void> ResetSoundSystem_t(ResetSoundSystem);
void ResetSoundSystem_r()
{
	if (reloadSound)
	{
		reloadSound = false;
		return;
	}

	ResetSoundSystem_t.Original();
}

//delete eyes tracker to avoid crash when swapping character
void EyeTracker_r(ObjectMaster* tp)
{
	pheadeyewk* eyewk = (pheadeyewk*)tp->EntityData2;

	if (eyewk)
	{
		auto pnum = eyewk->pnum;

		if (isMenuOpen(pnum))
		{
			memset(&eyewk->angy_head, 0, 88);
		}

		if (deleteEyeTracker[pnum])
		{
			FreeTask(tp);
			deleteEyeTracker[pnum] = false;
			return;
		}
	}

	EyeTracker_t.Original(tp);
}



//don't make the camera runs during menu to avoid it randomly moving when opening the menu
void CameraMain_r(ObjectMaster* tp)
{
	if (isMenuFullyOpenByAPlayer())
		return;

	CameraMain_t.Original(tp);
}

//series of hack to delete all the homing dash / attack effect to run and avoid crash with textures swap
void DoHomingAttackEffect_r(SonicCharObj2* a1, EntityData1* a2, EntityData2* a3, CharObj2Base* co2)
{
	if (DeleteHomingAttackEffect)
	{
		return;
	}

	DoHomingAttackEffect_t.Original(a1, a2, a3, co2);
}

static bool isAura = false;
void HomingAuraDisp_r(ObjectMaster* tp)
{
	if (isMenuOpenByAPlayer())
	{
		FreeTask(tp);
		return;
	}

	isAura = true;
	HomingDashAuraDisp_t.Original(tp);
	isAura = false;
}

bool isModelFromCharacter(NJS_OBJECT* obj)
{
	for (uint16_t i = 0; i < CharacterModels.size(); i++)
	{
		if (obj == CharacterModels[i].Model)
		{
			return true;
		}
	}

	return false;
}


bool isCallbackRunning = false;

TaskHook DisplayAfterImage_t(PlayerAfterimage_Disp);

void __cdecl DisplayAfterImage_r(ObjectMaster* a1)
{
	if (isMenuOpenByAPlayer())
	{
		FreeTask(a1);
		return;
	}

	isCallbackRunning = true;
	DisplayAfterImage_t.Original(a1);
	isCallbackRunning = false;
}


void __cdecl ProcessChunkModelsWithCallback_r(NJS_OBJECT* object, int(__cdecl* callback)(NJS_CNK_MODEL*))
{
	if (isMenuOpenByAPlayer())
	{
		return;
	}
	else if (isMenuOpenByAPlayer() == false && !isModelFromCharacter(object) && !isAura)
	{
		return;
	}

	isCallbackRunning = true;
	ProcessChunkModelsWithCallback(object, callback);
	isCallbackRunning = false;
}

//pause finalhazard task so players don't drop ring if menu is open
void LastBossPlayerManager_r(ObjectMaster* tp)
{
	if (isMenuFullyOpenByAPlayer())
	{
		if (ControllerEnabled[1] == 1)
		{
			memcpy(&Controllers[1], ControllerPointers[0], sizeof(PDS_PERIPHERAL));
			memcpy(&MenuButtons_Pressed[1], &MenuButtons_Pressed[0], sizeof(int));
			memcpy(&MenuButtons_Held[1], &MenuButtons_Held[0], sizeof(int));
			WriteAnalogs();
			UpdateUselessButtonPressBooleans();
		}

		return;
	}


	LastBossPlayerManager_t.Original(tp);
}

//Prevent most tasks of the game to run when the menu is open so we can pause the game and avoid crash when swapping skins
void __cdecl RunObjectIndex_r(int index)
{
	if (isMenuFullyOpenByAPlayer())
	{
		if (index > 0)
			return;

		ObjectMaster* obj_;
		ObjectMaster* objCopy;
		void(__cdecl * mainsub)(ObjectMaster*);
		ObjectMaster* previous;
		Bool v5;

		obj_ = ObjectLists[index];
		objCopy = obj_;
		if (obj_)
		{
			while (1)
			{
				mainsub = obj_->MainSub;
				previous = obj_->PrevObject;
				CurrentObjectSub = mainsub;
				if (mainsub)
				{
					mainsub(obj_);
				}
				v5 = obj_->Child == 0;
				CurrentObjectSub = 0;
				if (!v5)
				{
					sub_470CC0(obj_);
				}
				if (previous == objCopy)
				{
					break;
				}
				objCopy = ObjectLists[index];
				if (!objCopy)
				{
					break;
				}
				obj_ = previous;
			}
		}
	}
	else
	{
		RunObjectIndex_t.Original(index);
	}
}

void AlwaysLoadAltSkins()
{
	WriteData<2>((int*)0x716F2C, 0x90);
	WriteData<2>((int*)0x71748C, 0x90);
	WriteData<2>((int*)0x728241, 0x90);
	WriteData<2>((int*)0x728591, 0x90);
	WriteData<2>((int*)0x740D72, 0x90);
	WriteData<2>((int*)0x740FD2, 0x90);
}

void KnucklesToggleUpgradesDisplay(bool enable)
{
	if (!enable)
	{
		WriteJump((void*)0x72F4BD, (void*)0x72F616);
	}
	else
	{
		WriteData<1>((int*)0x72F4BD, 0x83);
		WriteData<1>((int*)0x72F4BE, 0x7C);
		WriteData<1>((int*)0x72F4BF, 0x24);
		WriteData<1>((int*)0x72F4C0, 0x10);
		WriteData<1>((int*)0x72F4C1, 0x1E);
	}
}

bool KnuxUpgradeExist()
{
	return CharacterModels[161].Model && CharacterModels[168].Model && CharacterModels[162].Model && CharacterModels[163].Model && CharacterModels[165].Model;
}

//unlike other characters, knuckles doesn't check for upgrades and always try to draw them which crash the game if they don't exist
//we patch this by forcing the game to not render them if the model doesn't exist.
TaskHook KnucklesDisplay_t(0x72EF20);

void KnucklesDisplay_r(ObjectMaster* tp)
{
	KnucklesToggleUpgradesDisplay(KnuxUpgradeExist());

	KnucklesDisplay_t.Original(tp);
}


void InitPatches()
{
	AlwaysLoadAltSkins();
	RunObjectIndex_t.Hook(RunObjectIndex_r);
	EyeTracker_t.Hook(EyeTracker_r);
	HomingDashAuraDisp_t.Hook(HomingAuraDisp_r);
	CameraMain_t.Hook(CameraMain_r);
	LastBossPlayerManager_t.Hook(LastBossPlayerManager_r);
	ResetSoundSystem_t.Hook(ResetSoundSystem_r); //fix level sounds not playing properly after skin swap
	KnucklesDisplay_t.Hook(KnucklesDisplay_r);
	DisplayAfterImage_t.Hook(DisplayAfterImage_r);

	WriteCall((void*)0x75668B, ProcessChunkModelsWithCallback_r); //homing aura display
	WriteCall((void*)0x756A2E, ProcessChunkModelsWithCallback_r); //jump aura display
	WriteCall((void*)0x757145, ProcessChunkModelsWithCallback_r); //homing dash aura
	WriteCall((void*)0x759ADF, ProcessChunkModelsWithCallback_r); //somersault aura	
	WriteCall((void*)0x7561FF, ProcessChunkModelsWithCallback_r); //spin dash aura Display	
	WriteCall((void*)0x756D77, ProcessChunkModelsWithCallback_r); //???	
	WriteCall((void*)0x476B60, ProcessChunkModelsWithCallback_r); //after image
}