#include "pch.h"
#include "menu.h"

bool deleteTime = false;
bool DeleteHomingAttackEffect = false;

FunctionHook<void, ObjectMaster*> EyeTracker_t(0x4766C0);
UsercallFuncVoid(DoHomingAttackEffect_t,
	(SonicCharObj2* sco2, EntityData1* twp, EntityData2* mwp, CharObj2Base* co2), (sco2, twp, mwp, co2), 0x720E00, rEBX, stack4, stack4, stack4);

/**UsercallFuncVoid(DoHomingAttackAura_t, (ObjectMaster* tp), (tp), 0x7566C0, rEDI);

UsercallFuncVoid(DoJumpAura_t, (ObjectMaster* tp), (tp), 0x756AE0, rEDI);
UsercallFuncVoid(SpinDashAura_t, (ObjectMaster* tp), (tp), 0x7562A0, rEDI);
FunctionHook<void, ObjectMaster*> SpinDashAuraDisplay_t(0x756040);*/
FunctionHook<void, ObjectMaster*> HomingDashAuraDisp_t(0x757040);


void EyeTracker_r(ObjectMaster* tp)
{
	if (deleteTime)
	{
		FreeTask(tp);
		deleteTime = false;
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


void InitPatches()
{
	EyeTracker_t.Hook(EyeTracker_r);
	HomingDashAuraDisp_t.Hook(HomingAuraDisp_r);
	/**DoHomingAttackAura_t.Hook(DoHomingAura_r);
	DoHomingAttackEffect_t.Hook(DoHomingAttackEffect_r);
	DoJumpAura_t.Hook(DoJumpAura_r);
	SpinDashAuraDisplay_t.Hook(SpinDashAuraDisp_r);
	SpinDashAura_t.Hook(SpinDashAura_r);*/

	WriteCall((void*)0x75668B, ProcessChunkModelsWithCallback_r); //homing aura display
	WriteCall((void*)0x756A2E, ProcessChunkModelsWithCallback_r); //jump aura display
	WriteCall((void*)0x757145, ProcessChunkModelsWithCallback_r); //homing dash aura
	WriteCall((void*)0x759ADF, ProcessChunkModelsWithCallback_r); //somersault aura	
	WriteCall((void*)0x7561FF, ProcessChunkModelsWithCallback_r); //spin dash aura Display	
	WriteCall((void*)0x756D77, ProcessChunkModelsWithCallback_r); //???	
	WriteCall((void*)0x476B60, ProcessChunkModelsWithCallback_r); //after image
}