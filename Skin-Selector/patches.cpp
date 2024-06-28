#include "pch.h"
#include "menu.h"

bool deleteEyeTracker = false;
bool DeleteHomingAttackEffect = false;

TaskHook EyeTracker_t(0x4766C0);
UsercallFuncVoid(DoHomingAttackEffect_t,
	(SonicCharObj2* sco2, EntityData1* twp, EntityData2* mwp, CharObj2Base* co2), (sco2, twp, mwp, co2), 0x720E00, rEBX, stack4, stack4, stack4);

TaskHook HomingDashAuraDisp_t(0x757040);
TaskHook CameraMain_t(cameraCons_Main);
FunctionHook<void, int> RunObjectIndex_t(RunObjectIndex);

//don't make the camera runs during menu
void CameraMain_r(ObjectMaster* tp)
{
	if (isMenuFullyOpenByAPlayer())
		return;

	CameraMain_t.Original(tp);
}

void EyeTracker_r(ObjectMaster* tp)
{
	if (deleteEyeTracker)
	{
		FreeTask(tp);
		deleteEyeTracker = false;
		return;
	}

	EyeTracker_t.Original(tp);
}

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

FunctionHook<void, NJS_OBJECT*, int(__cdecl*)(NJS_CNK_MODEL*)>ProcessChunkModelsWithCallback_t(ProcessChunkModelsWithCallback);
void __cdecl ProcessChunkModelsWithCallback_r(NJS_OBJECT* object, int(__cdecl* callback)(NJS_CNK_MODEL*))
{
	if (isMenuOpenByAPlayer())
		return;
	else if (isMenuOpenByAPlayer() == false && !isModelFromCharacter(object) && !isAura)
	{
		return;
	}

	isCallbackRunning = true;
	ProcessChunkModelsWithCallback(object, callback);
	isCallbackRunning = false;
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


void InitPatches()
{
	RunObjectIndex_t.Hook(RunObjectIndex_r);
	EyeTracker_t.Hook(EyeTracker_r);
	HomingDashAuraDisp_t.Hook(HomingAuraDisp_r);
	CameraMain_t.Hook(CameraMain_r);

	WriteCall((void*)0x75668B, ProcessChunkModelsWithCallback_r); //homing aura display
	WriteCall((void*)0x756A2E, ProcessChunkModelsWithCallback_r); //jump aura display
	WriteCall((void*)0x757145, ProcessChunkModelsWithCallback_r); //homing dash aura
	WriteCall((void*)0x759ADF, ProcessChunkModelsWithCallback_r); //somersault aura	
	WriteCall((void*)0x7561FF, ProcessChunkModelsWithCallback_r); //spin dash aura Display	
	WriteCall((void*)0x756D77, ProcessChunkModelsWithCallback_r); //???	
	WriteCall((void*)0x476B60, ProcessChunkModelsWithCallback_r); //after image
}