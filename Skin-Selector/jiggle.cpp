#include "pch.h"

//handle vertex anims patches

void LoadSonicJiggle(SonicCharObj2* sco2)
{
	sco2->SpineJiggle = LoadJiggle(CharacterModels[21].Model->child);
	sco2->SpineJiggle->type = 18;
	sco2->SpineJiggle->speed = 0.40f;
	sco2->SpineJiggle->field_8 = 0;
	sco2->SpineJiggle->field_10 = 1024;
	sco2->SpineJiggle->Model = 0;
	sco2->SpineJigglePos = MainCharObj1[sco2->base.PlayerNum]->Position;
}

void LoadShadowJiggle(SonicCharObj2* sco2)
{
	sco2->SpineJiggle = LoadJiggle(CharacterModels[86].Model->child);
	sco2->SpineJiggle->type = 19;
	sco2->SpineJiggle->speed = 0.40f;
	sco2->SpineJiggle->field_8 = 0;
	sco2->SpineJiggle->field_10 = 1024;
	sco2->SpineJiggle->Model = 0;
	sco2->SpineJigglePos = MainCharObj1[sco2->base.PlayerNum]->Position;
}

void LoadAmyJiggle(SonicCharObj2* sco2)
{
	sco2->SpineJiggle = LoadJiggle(CharacterModels[414].Model->child);
	sco2->SpineJiggle->type = 18;
	sco2->SpineJiggle->speed = 0.40f;
	sco2->SpineJiggle->field_8 = 0;
	sco2->SpineJiggle->field_10 = 1024;
	sco2->SpineJiggle->Model = 0;
	sco2->SpineJigglePos = MainCharObj1[sco2->base.PlayerNum]->Position;
}

void LoadMilesJiggle(TailsCharObj2New* mco2)
{
	mco2->tailJiggle0 = LoadJiggle(CharacterModels[222].Model);
	mco2->tailJiggle0->type = 6;
	mco2->tailJiggle0->speed = 0.40f;
	mco2->tailJiggle0->field_8 = 12288;
	mco2->tailJiggle0->field_10 = 1792;
	mco2->tailJiggle0->Model = CharacterModels[228].Model;
	mco2->tailJiggle0->OtherModel = CharacterModels[229].Model;
	mco2->tailJiggle0->SourceModelCopy->evalflags &= 0xFFFFFFFD;
	mco2->tailJiggle1 = LoadJiggle(CharacterModels[222].Model);
	mco2->tailJiggle1->type = 6;
	mco2->tailJiggle1->speed = 0.40f;
	mco2->tailJiggle1->field_8 = 53248;
	mco2->tailJiggle1->field_10 = 1792;
	mco2->tailJiggle1->Model = CharacterModels[228].Model;
	mco2->tailJiggle1->OtherModel = CharacterModels[229].Model;
	mco2->tailJiggle1->SourceModelCopy->evalflags &= 0xFFFFFFFD;
}

void LoadKnuxJiggle(KnucklesCharObj2* kco2)
{
	kco2->HeadJiggle = LoadJiggle(CharacterModels[156].Model->child);
	kco2->HeadJiggle->type = 15;
	kco2->HeadJiggle->speed = 0.40f;
	kco2->HeadJiggle->field_8 = 0;
	kco2->HeadJiggle->field_10 = 1024;
	kco2->HeadJiggle->Model = CharacterModels[166].Model;
	kco2->HeadJigglePos = MainCharObj1[kco2->base.PlayerNum]->Position;
}

void LoadRougeJiggle(KnucklesCharObj2* kco2, bool isAlt)
{
	//crash with rouge alt
	if (isAlt == false)
	{
		kco2->UpperTorsoJiggle = LoadJiggle(CharacterModels[174].Model->child);
		kco2->UpperTorsoJiggle->type = 14;
		kco2->UpperTorsoJiggle->speed = 0.40f;
		kco2->UpperTorsoJiggle->field_8 = 12288;
		kco2->UpperTorsoJiggle->field_10 = 1024;
		kco2->UpperTorsoJiggle->Model = CharacterModels[174].Model->child;
	}

	kco2->LowerTorsoJiggle = LoadJiggle(CharacterModels[174].Model);
	kco2->LowerTorsoJiggle->type = 13;
	kco2->LowerTorsoJiggle->speed = 0.40f;
	kco2->LowerTorsoJiggle->field_8 = 12288;
	kco2->LowerTorsoJiggle->field_10 = 1024;
	kco2->LowerTorsoJiggle->Model = CharacterModels[174].Model;
	kco2->TorsoJigglePos = MainCharObj1[kco2->base.PlayerNum]->Position;

	kco2->HeadJiggle = LoadJiggle(CharacterModels[186].Model->child);
	kco2->HeadJiggle->type = 17;
	kco2->HeadJiggle->speed = 0.40f;
	kco2->HeadJiggle->field_8 = 0;
	kco2->HeadJiggle->field_10 = 1024;
	kco2->HeadJiggle->Model = CharacterModels[186].Model->child;
	kco2->HeadJigglePos = MainCharObj1[kco2->base.PlayerNum]->Position;
}

void LoadTikalJiggle(KnucklesCharObj2* tco2)
{
	tco2->HeadJiggle = LoadJiggle(CharacterModels[496].Model->child);
	tco2->HeadJiggle->type = 15;
	tco2->HeadJiggle->speed = 0.40f;
	tco2->HeadJiggle->field_8 = 0;
	tco2->HeadJiggle->field_10 = 1024;
	tco2->HeadJiggle->Model = CharacterModels[501].Model;
	tco2->HeadJigglePos = MainCharObj1[tco2->base.PlayerNum]->Position;
}

void LoadSuperSonicJiggle(SuperSonicCharObj2* sco2)
{
	sco2->SpineJiggle = LoadJiggle(CharacterModels[349].Model->child);
	sco2->SpineJiggle->type = 18;
	sco2->SpineJiggle->speed = 0.40f;
	sco2->SpineJiggle->field_8 = 0;
	sco2->SpineJiggle->field_10 = 1024;
	sco2->SpineJiggle->Model = 0;
	sco2->SpineJigglePos = MainCharObj1[sco2->base.PlayerNum]->Position;
}

void LoadSuperShadowJiggle(SuperSonicCharObj2* sco2)
{
	sco2->SpineJiggle = LoadJiggle(CharacterModels[376].Model->child);
	sco2->SpineJiggle->type = 19;
	sco2->SpineJiggle->speed = 0.40f;
	sco2->SpineJiggle->field_8 = 0;
	sco2->SpineJiggle->field_10 = 1024;
	sco2->SpineJiggle->Model = 0;
	sco2->SpineJigglePos = MainCharObj1[sco2->base.PlayerNum]->Position;
}

void CheckAndLoadJiggle(const uint8_t pnum, const uint8_t charID2)
{
	if (saveSkin)
	{
		if (currentSkin[pnum][charID2].DisableJiggle == false || isLegacy(currentSkin[pnum][charID2].Type))
		{
			void* spePwk = MainCharacter[pnum]->Data2.Undefined;
			auto sCO2 = (SonicCharObj2*)spePwk;
			auto mCO2 = (TailsCharObj2New*)spePwk;
			auto kCO2 = (KnucklesCharObj2*)spePwk;
			auto meCO2 = (MechEggmanCharObj2*)spePwk;
			auto SSCo2 = (SuperSonicCharObj2*)spePwk;

			switch (charID2)
			{
			case Characters_Sonic:
				LoadSonicJiggle(sCO2);
				break;
			case Characters_Shadow:
				LoadShadowJiggle(sCO2);
				break;
			case Characters_Amy:
				LoadAmyJiggle(sCO2);
				break;
			case Characters_Tails:
				LoadMilesJiggle(mCO2);
				break;
			case Characters_Knuckles:
				LoadKnuxJiggle(kCO2);
				break;
			case Characters_Rouge:
				LoadRougeJiggle(kCO2, isAlt(currentSkin[pnum][charID2].Type));
				break;
			case Characters_Tikal:
				LoadTikalJiggle(kCO2);
				break;
			case Characters_SuperSonic:
				LoadSuperSonicJiggle(SSCo2);
				break;
			case Characters_SuperShadow:
				LoadSuperShadowJiggle(SSCo2);
				break;

			}
		}
	}
}


//original code: https://github.com/Ngolinvaux/DisableSA2Jiggle/blob/main/main.cpp
const void* const loc_71729f = (const void*)0x71729f;
__declspec(naked) void thingAmy() {
	__asm {

		sub esp, 4
		jmp loc_71729f
	}
}


const void* const loc_717028 = (const void*)0x717028;
__declspec(naked) void thingSonic() {
	__asm {
		mov esi, [esp + 0Ch]
		sub esp, 4
		jmp loc_717028
	}
}
const void* const loc_7287c0 = (const void*)0x7287c0;
__declspec(naked) void thingRouge() {
	__asm {
		mov esi, [esp + 0Ch]
		sub esp, 4
		jmp loc_7287c0
	}
}
const void* const loc_717588 = (const void*)0x717588;
__declspec(naked) void thingShadow() {
	__asm {
		mov esi, [esp + 0Ch]
		sub esp, 4
		jmp loc_717588
	}
}
const void* const loc_728399 = (const void*)0x728399;
__declspec(naked) void thingKnux() {
	__asm {
		mov esi, [esp + 0Ch]
		sub esp, 4
		jmp loc_728399
	}
}

const void* const loc_728a8a = (const void*)0x728a8a;
__declspec(naked) void thingTikal() {
	__asm {

		sub esp, 4
		jmp loc_728a8a
	}
}
const void* const loc_49ab13 = (const void*)0x49ab13;
__declspec(naked) void thingSuperSonic() {
	__asm {

		sub esp, 4
		jmp loc_49ab13
	}
}
const void* const loc_49ad77 = (const void*)0x49ad77;
__declspec(naked) void thingSuperShadow() {
	__asm {

		sub esp, 4
		jmp loc_49ad77
	}
}

void InitJiggleHacks()
{
	if (saveSkin) //disable all jiggles, we will manually load them later due to skins that don't handle those
	{
		WriteJump((void*)0x716FDD, thingSonic);
		WriteJump((void*)0x71753d, thingShadow);
		WriteJump((void*)0x728346, thingKnux);
		WriteJump((void*)0x728696, thingRouge);
		WriteJump((void*)0x717257, thingAmy);
		WriteJump((void*)0x49aacb, thingSuperSonic);
		WriteJump((void*)0x49ad2f, thingSuperShadow);
		WriteJump((void*)0x728a3c, thingTikal);
		WriteData<3>((void*)0x728a8e, 0x90); // tikal jiggle
	}
}