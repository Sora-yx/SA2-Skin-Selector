#include "pch.h"
#include <iostream>
#include <filesystem>
#include "FileSystem.h"
#include "menu.h"
#include <Shlwapi.h>
#include "patches.h"
#include "save.h"

std::vector<SkinMod> skinList;
SkinMod currentSkin[PMax][CharMax];

CharInfo SonicLegacyInfo[] =
{
	{ "SONICMDL", "SONICTEX", "SONICMTN", "s_efftex", "zanki_sonic", "itemp_1up"},
	{ "SONIC1MDL", "SONIC1TEX", "SONICMTN", "s_efftex", "zanki_sonic", "itemp_1up"},
};

SkinMod SonicLegacy[] =
{
	{ Characters_Sonic, "Sonic (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, SonicLegacyInfo[0]},
	{ Characters_Sonic, "Sonic (Race Costume)", "Sonic Team", "Desc", "", "", 1, LegacyAlt, false, SonicLegacyInfo[1] },
};

CharInfo ShadowLegacyInfo[] =
{
	{ "TERIOSMDL", "TERIOSTEX", "TERIOSMTN", "sh_efftex", "zanki_shadow", "itemp_1up4"},
	{ "SHADOW1MDL", "SHADOW1TEX", "TERIOSMTN", "sh_efftex", "zanki_shadow", "itemp_1up4"},
};

SkinMod ShadowLegacy[] =
{
	{ Characters_Shadow, "Shadow (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, ShadowLegacyInfo[0]},
	{ Characters_Shadow, "Shadow (Race Costume)", "Sonic Team", "Desc", "", "", 1, LegacyAlt, false, ShadowLegacyInfo[1] },
};

CharInfo MilesLegacyInfo =
{
	"MILESMDL", "MILESTEX", "MILESMTN", "", "zanki_tails", "itemp_1up3"
};


SkinMod MilesLegacy = { Characters_Tails, "Tails (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, MilesLegacyInfo };

CharInfo EggmanLegacyInfo =
{
	 "EGGMDL", "EGGTEX", "EGGMTN", "", "zanki_egg1", "itemp_1up6"
};

SkinMod EggmanLegacy = { Characters_Eggman, "Eggman (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, EggmanLegacyInfo };

CharInfo KnuxLegacyInfo[] =
{
	{ "KNUCKMDL", "KNUCKTEX", "KNUCKLMTN", "k_efftex", "zanki_knuckle", "itemp_1up2"},
	{ "BKNUCKMDL", "BKNUCKTEX", "KNUCKLMTN", "k_efftex", "zanki_knuckle", "itemp_1up2"},
};

SkinMod KnuxLegacy[] =
{
	{ Characters_Knuckles, "Knuckles (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, KnuxLegacyInfo[0] },
	{ Characters_Knuckles, "Knuckles (Jumpsuit Costume)", "Sonic Team", "Desc", "", "", 1, LegacyAlt, false, KnuxLegacyInfo[1] },
};

CharInfo RougeLegacyInfo[] =
{
	{ "ROUGEMDL", "ROUGETEX", "ROUGEMTN", "r_efftex", "zanki_rouge", "itemp_1up5"},
	{ "BROUGEMDL", "BROUGETEX", "ROUGEMTN", "r_efftex", "zanki_rouge", "itemp_1up5"},
};

SkinMod RougeLegacy[] =
{
	{ Characters_Rouge, "Rouge (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, RougeLegacyInfo[0] },
	{ Characters_Rouge, "Rouge (Two-piece Costume)", "Sonic Team", "Desc", "", "", 1, LegacyAlt, false, RougeLegacyInfo[1] },
};

CharInfo MechTailsLegacyInfo[] =
{
	{ "TWALKMDL", "TWALKTEX", "TWALKMTN", "", "zanki_tails", "itemp_1up3"},
	{ "TWALK1MDL", "TWALK1TEX", "TWALKMTN", "", "zanki_tails", "itemp_1up3"},
};

SkinMod MechTailsLegacy[] =
{
	{ Characters_MechTails, "Mech Tails (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, MechTailsLegacyInfo[0] },
	{ Characters_MechTails, "Mech Tails (Red Tornado)", "Sonic Team", "Desc", "", "", 1, LegacyAlt, false, MechTailsLegacyInfo[1] },
};

CharInfo MechEggmanLegacyInfo[] =
{
	{ "EWALKMDL", "EWALKTEX", "EWALKMTN", "", "zanki_egg1", "itemp_1up3"},
	{ "EWALK2MDL", "EWALK2TEX", "EWALKMTN", "", "zanki_egg1", "itemp_1up3"},
};

SkinMod MechEggmanLegacy[] =
{
	{ Characters_MechEggman, "Mech Eggman (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, MechEggmanLegacyInfo[0] },
	{ Characters_MechEggman, "Mech Eggman (Camouflage)", "Sonic Team", "Desc", "", "", 1, LegacyAlt, false, MechEggmanLegacyInfo[1] },
};

CharInfo AmyLegacyInfo =
{
	 "AMYMDL", "AMYTEX", "AMYMTN", "amy_efftex", "zanki_amy", "",
};

SkinMod AmyLegacy = { Characters_Amy, "Amy (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, AmyLegacyInfo };

CharInfo MSLegacyInfo =
{
	 "METALSONICMDL", "METALSONICTEX", "METALSONICMTN", "S_EFFTEX", "zanki_metal", "",
};

SkinMod MSLegacy = { Characters_MetalSonic, "Metal Sonic (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, MSLegacyInfo };

CharInfo TikalLegacyInfo =
{
	"TICALMDL", "TICALTEX", "TICALMTN", "k_efftex", "zanki_tical", ""
};

SkinMod TikalLegacy = { Characters_Tikal, "Tikal (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, TikalLegacyInfo };


CharInfo ChaosLegacyInfo =
{
	"CHAOS0MDL", "CHAOS0TEX", "CHAOS0MTN", "c0_efftex", "zanki_chaos0", ""
};

SkinMod ChaosLegacy = { Characters_Chaos, "Chaos 0 (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, ChaosLegacyInfo };

CharInfo SSLegacyInfo =
{
	"SSONICMDL", "SSONICTEX", "SSONICMTN", "SSONEFFTEX", "zanki_supersonic", ""
};

SkinMod SSLegacy = { Characters_SuperSonic, "Super Sonic (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, SSLegacyInfo };

CharInfo SSHLegacyInfo =
{
	"SSHADOWMDL", "SSHADOWTEX", "SSHADOWMTN", "SSONEFFTEX", "zanki_supershadow", ""
};

SkinMod SSHLegacy = { Characters_SuperShadow, "Super Shadow (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, SSHLegacyInfo };

static const std::unordered_map<std::string, uint8_t> charnamemap = {
	{ "sonic", Characters_Sonic },
	{ "shadow", Characters_Shadow },
	{ "tails", Characters_Tails },
	{ "miles", Characters_Tails },
	{ "eggman", Characters_Eggman },
	{ "knuckles", Characters_Knuckles },
	{ "rouge", Characters_Rouge },
	{ "mechtails", Characters_MechTails},
	{ "mecheggman", Characters_MechEggman},
	{ "amy", Characters_Amy},
	{ "supersonic", Characters_SuperSonic},
	{ "supershadow", Characters_SuperShadow},
	{ "b", Characters_B}, //unused
	{ "metalsonic", Characters_MetalSonic},
	{ "chaowalker", Characters_ChaoWalker},
	{ "darkchaowalker", Characters_DarkChaoWalker},
	{ "tikal", Characters_Tikal},
	{ "chaos", Characters_Chaos}
};

uint8_t getCharacterValue(const std::string& key)
{
	if (is_number(key))
	{
		const uint8_t id = std::stoi(key);

		if (id >= Characters_Sonic && id <= CharMax)
			return id;
	}
	else
	{
		auto it = charnamemap.find(key);
		if (it != charnamemap.end())
		{
			return it->second;
		}
	}

	return Characters_Sonic;
}


Sint32 GetSkinListIndex(const uint16_t uniqueID)
{
	for (uint16_t i = 0; i < skinList.size(); i++)
	{
		if (skinList[i].uniqueID == uniqueID)
			return i;
	}

	return -1;
}

static SkinMenuItem* GetSelectedSkin(const uint8_t pnum)
{
	auto skin = GetSelectedItem(pnum);

	if (skin && GetSkinListIndex(skin->data.uniqueID) >= 0)
		return skin;

	return nullptr;
}


bool isLegacy(SkinType type)
{
	return type == Legacy || type == LegacyAlt;
}

bool isAlt(SkinType type)
{
	return type == Alt || type == LegacyAlt;
}

std::string GetPakOrPrsTexture(const char* folderPath, const char* texName)
{
	//first, check if the extension has been included in the tex archive name
	std::string curTex = folderPath + (std::string)"\\gd_PC\\" + texName;
	curTex = normalizePath(curTex.c_str());

	if (FileExists(curTex))
		return curTex;

	//check if the extension has been included with pak
	curTex = folderPath + (std::string)"\\gd_PC\\PRS\\" + texName;
	curTex = normalizePath(curTex.c_str());

	if (FileExists(curTex))
		return curTex;

	curTex = folderPath + (std::string)"\\gd_PC\\" + texName + ".prs";
	curTex = normalizePath(curTex.c_str());

	if (FileExists(curTex))
		return curTex;

	curTex = folderPath + (std::string)"\\gd_PC\\" + texName + ".GVR";
	curTex = normalizePath(curTex.c_str());

	if (FileExists(curTex))
		return curTex;

	//if still not found, assume it's a simple PAK.
	curTex = folderPath + (std::string)"\\gd_PC\\PRS\\" + texName + ".pak";
	curTex = normalizePath(curTex.c_str());

	if (FileExists(curTex))
		return curTex;

	return "";
}

std::string GetCharTexturePath(const char* texName, std::string folderPath, std::string legacyTexName)
{
	std::string s = GetPakOrPrsTexture(folderPath.c_str(), texName);

	if (s == "")
		s = GetPakOrPrsTexture(folderPath.c_str(), legacyTexName.c_str());

	return s;
}

std::vector<std::string> replacedFiles[CharMax];


void unReplaceFiles(uint8_t charID2)
{
	for (uint16_t i = 0; i < replacedFiles[charID2].size(); i++)
		HelperFunctionsGlobal.UnreplaceFile(replacedFiles[charID2].at(i).c_str());

	replacedFiles[charID2].clear();
}

static void scanPRSFolder_int(const uint8_t charID2, const std::string& srcPath, int srcLen)
{
	WIN32_FIND_DATAA data;
	char path[MAX_PATH];
	snprintf(path, sizeof(path), "%s\\prs\\*", srcPath.c_str());
	HANDLE hFind = FindFirstFileA(path, &data);

	// No files found.
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		// NOTE: This will hide *all* files starting with '.'.
		// SA2 doesn't use any files starting with '.',
		// so this won't cause any problems.

		if (data.cFileName[0] == '.' || data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;

		std::string name = data.cFileName;

		auto ext = GetExtension(name);

		if (ext != "pak" && ext != "prs" && ext != "pvmx")
			continue;

		// Create the mod filename and original filename.
		std::string modFile = srcPath + "\\prs\\" + data.cFileName;
		transform(modFile.begin(), modFile.end(), modFile.begin(), ::tolower);


		// Original filename.
		std::string origFile = "resource\\gd_pc\\";
		if (srcPath.size() > (size_t)srcLen)
			origFile += srcPath.substr(srcLen) + '\\';
		origFile += name;
		transform(origFile.begin(), origFile.end(), origFile.begin(), ::tolower);

		ReplaceFileExtension(origFile, ".prs");
		HelperFunctionsGlobal.ReplaceFile(origFile.c_str(), modFile.c_str());
		replacedFiles[charID2].push_back(origFile);

		ReplaceFileExtension(origFile, ".gvr");
		HelperFunctionsGlobal.ReplaceFile(origFile.c_str(), modFile.c_str());
		replacedFiles[charID2].push_back(origFile);


	} while (FindNextFileA(hFind, &data) != 0);

	FindClose(hFind);
}

static void scanFolder_ReplaceFile(const uint8_t charID2, const std::string& srcPath, int srcLen)
{
	WIN32_FIND_DATAA data;
	char path[MAX_PATH];
	snprintf(path, sizeof(path), "%s\\*", srcPath.c_str());
	HANDLE hFind = FindFirstFileA(path, &data);

	// No files found.
	if (hFind == INVALID_HANDLE_VALUE)
		return;

	do
	{
		// NOTE: This will hide *all* files starting with '.'.
		// SA2 doesn't use any files starting with '.',
		// so this won't cause any problems.
		if (data.cFileName[0] == '.')
		{
			continue;
		}

		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (!_stricmp(data.cFileName, "prs"))
				scanPRSFolder_int(charID2, srcPath, srcLen);

			// Recursively scan this directory.
			const std::string newSrcPath = srcPath + '\\' + std::string(data.cFileName);
			scanFolder_ReplaceFile(charID2, newSrcPath, srcLen);
			continue;
		}

		// Create the mod filename and original filename.
		std::string modFile = srcPath + '\\' + std::string(data.cFileName);
		transform(modFile.begin(), modFile.end(), modFile.begin(), ::tolower);

		// Original filename.
		std::string origFile = "resource\\gd_pc\\" + modFile.substr(srcLen);

		HelperFunctionsGlobal.ReplaceFile(origFile.c_str(), modFile.c_str());
		replacedFiles[charID2].push_back(origFile);
	} while (FindNextFileA(hFind, &data) != 0);

	FindClose(hFind);
}

void SkinReplaceFiles(const char* folderPath, const uint8_t charID2)
{
	const std::string gdModPath = folderPath + (std::string)"\\gd_PC";
	scanFolder_ReplaceFile(charID2, gdModPath, gdModPath.length() + 1);
}

static void LoadSonicJiggle(SonicCharObj2* sco2)
{
	sco2->SpineJiggle = LoadJiggle(CharacterModels[21].Model->child);
	sco2->SpineJiggle->type = 18;
	sco2->SpineJiggle->speed = 0.40f;
	sco2->SpineJiggle->field_8 = 0;
	sco2->SpineJiggle->field_10 = 1024;
	sco2->SpineJiggle->Model = 0;
	sco2->SpineJigglePos = MainCharObj1[sco2->base.PlayerNum]->Position;
}

static void LoadShadowJiggle(SonicCharObj2* sco2)
{
	sco2->SpineJiggle = LoadJiggle(CharacterModels[86].Model->child);
	sco2->SpineJiggle->type = 19;
	sco2->SpineJiggle->speed = 0.40f;
	sco2->SpineJiggle->field_8 = 0;
	sco2->SpineJiggle->field_10 = 1024;
	sco2->SpineJiggle->Model = 0;
	sco2->SpineJigglePos = MainCharObj1[sco2->base.PlayerNum]->Position;
}

static void LoadAmyJiggle(SonicCharObj2* sco2)
{
	sco2->SpineJiggle = LoadJiggle(CharacterModels[414].Model->child);
	sco2->SpineJiggle->type = 18;
	sco2->SpineJiggle->speed = 0.40f;
	sco2->SpineJiggle->field_8 = 0;
	sco2->SpineJiggle->field_10 = 1024;
	sco2->SpineJiggle->Model = 0;
	sco2->SpineJigglePos = MainCharObj1[sco2->base.PlayerNum]->Position;
}

static void LoadMilesJiggle(TailsCharObj2New* mco2)
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

static void LoadKnuxJiggle(KnucklesCharObj2* kco2)
{
	kco2->HeadJiggle = LoadJiggle(CharacterModels[156].Model->child);
	kco2->HeadJiggle->type = 15;
	kco2->HeadJiggle->speed = 0.40f;
	kco2->HeadJiggle->field_8 = 0;
	kco2->HeadJiggle->field_10 = 1024;
	kco2->HeadJiggle->Model = CharacterModels[166].Model;
	kco2->HeadJigglePos = MainCharObj1[kco2->base.PlayerNum]->Position;
}

static void LoadRougeJiggle(KnucklesCharObj2* kco2, bool isAlt)
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

static void LoadTikalJiggle(KnucklesCharObj2* tco2)
{
	tco2->HeadJiggle = LoadJiggle(CharacterModels[496].Model->child);
	tco2->HeadJiggle->type = 15;
	tco2->HeadJiggle->speed = 0.40f;
	tco2->HeadJiggle->field_8 = 0;
	tco2->HeadJiggle->field_10 = 1024;
	tco2->HeadJiggle->Model = CharacterModels[501].Model;
	tco2->HeadJigglePos = MainCharObj1[tco2->base.PlayerNum]->Position;
}

static void LoadSuperSonicJiggle(SuperSonicCharObj2* sco2)
{
	sco2->SpineJiggle = LoadJiggle(CharacterModels[349].Model->child);
	sco2->SpineJiggle->type = 18;
	sco2->SpineJiggle->speed = 0.40f;
	sco2->SpineJiggle->field_8 = 0;
	sco2->SpineJiggle->field_10 = 1024;
	sco2->SpineJiggle->Model = 0;
	sco2->SpineJigglePos = MainCharObj1[sco2->base.PlayerNum]->Position;
}

static void LoadSuperShadowJiggle(SuperSonicCharObj2* sco2)
{
	sco2->SpineJiggle = LoadJiggle(CharacterModels[376].Model->child);
	sco2->SpineJiggle->type = 19;
	sco2->SpineJiggle->speed = 0.40f;
	sco2->SpineJiggle->field_8 = 0;
	sco2->SpineJiggle->field_10 = 1024;
	sco2->SpineJiggle->Model = 0;
	sco2->SpineJigglePos = MainCharObj1[sco2->base.PlayerNum]->Position;
}

static NJS_TEXLIST* GetEffTexlist(uint8_t charID, const uint8_t pnum)
{
	KnucklesCharObj2* kCo2 = (KnucklesCharObj2*)MainCharacter[pnum]->Data2.Entity;
	switch (charID)
	{
	case Characters_Sonic:
		return &Texlist_SonEff;
	case Characters_Shadow:
		return &Texlist_ShadEff;
	case Characters_Amy:
		return &Texlist_AmyEff;
	case Characters_MetalSonic:
		return &Texlist_MetEff;
	case Characters_Knuckles:
	case Characters_Rouge:
	case Characters_Chaos:
		return kCo2->EffectTextureList;
	case Characters_SuperSonic:
	case Characters_SuperShadow:
		return &SSONEFFTEX_TEXLIST;
	}

	return nullptr;
}

static void LoadCharEffTextures(uint8_t charID, const char* texName)
{
	switch (charID)
	{
	case Characters_Sonic:
		LoadTextureList(texName, &Texlist_SonEff);
		break;
	case Characters_Shadow:
		LoadTextureList(texName, &Texlist_ShadEff);
		break;
	case Characters_Amy:
		LoadTextureList(texName, &Texlist_AmyEff);
		break;
	case Characters_MetalSonic:
		LoadTextureList(texName, &Texlist_MetEff);
		break;
	case Characters_SuperSonic:
	case Characters_SuperShadow:
		LoadTextureList(texName, &SSONEFFTEX_TEXLIST);
		break;
	}
}


static void LoadEffTex(CharInfo* info, const uint8_t pnum, const uint8_t charID2)
{
	NJS_TEXLIST* texlistEff = GetEffTexlist(charID2, pnum);
	if (texlistEff)
		FreeTexList(texlistEff);
	if (MainCharObj2[pnum]->CharID == Characters_Knuckles || MainCharObj2[pnum]->CharID == Characters_Rouge)
	{
		if (texlistEff)
			FreeMemory((int*)texlistEff, (char*)"..\\..\\src\\figure\\knuckles\\knuckles.c", 5464);
		KnucklesCharObj2* kCo2 = (KnucklesCharObj2*)MainCharacter[pnum]->Data2.Entity;
		kCo2->EffectTextureList = LoadCharTextures(info->effTexName.c_str());
	}
	else
	{
		LoadCharEffTextures(charID2, info->effTexName.c_str());
	}
}

static void LoadLifeIcon(CharInfo* info, const uint8_t charID2)
{
	FreeTexList(LifeIconTexs[charID2]);
	LoadTextureList_NoName(LifeIconTexs[charID2]);
}

static void LoadExtraTextures(CharInfo* info, const uint8_t pnum, const uint8_t charID2)
{
	//restore eff tex
	LoadEffTex(info, pnum, charID2);
	LoadLifeIcon(info, charID2);
}

static bool HasCustomAnims(CharInfo* info, const char* folderPath)
{
	std::string animPath = folderPath + (std::string)"\\gd_PC\\" + info->animName + ".PRS";
	animPath = normalizePath(animPath.c_str());
	return FileExists(animPath);
}

static void ReplaceAnimations(CharInfo* info, const char* folderPath, const uint8_t pnum, bool hadCustomAnim = false)
{
	std::string animPath = folderPath + (std::string)info->animName + ".PRS";
	animPath = normalizePath(animPath.c_str());

	if (FileExists(animPath) || hadCustomAnim)
	{
		auto p = MainCharObj2[pnum];
		const std::string animName = info->animName + (std::string)".PRS";

		void* spePwk = MainCharacter[pnum]->Data2.Undefined;
		auto sCO2 = (SonicCharObj2*)spePwk;
		auto mCO2 = (TailsCharObj2*)spePwk;
		auto eCO2 = (EggmanCharObj2*)spePwk;
		auto kCO2 = (KnucklesCharObj2*)spePwk;
		auto meCO2 = (MechEggmanCharObj2*)spePwk;
		auto SSCo2 = (SuperSonicCharObj2*)spePwk;

		switch (p->CharID)
		{
		case Characters_Sonic:
		case Characters_Shadow:
			UnloadAnimation(sCO2->MotionList);
			sCO2->MotionList = LoadMTNFile((char*)animName.c_str());
			break;
		case Characters_Tails:
			UnloadAnimation(mCO2->MotionList);
			mCO2->MotionList = LoadMTNFile((char*)animName.c_str());
			break;
		case Characters_Eggman:
			UnloadAnimation(eCO2->MotionList);
			eCO2->MotionList = LoadMTNFile((char*)animName.c_str());
			break;
		case Characters_Knuckles:
		case Characters_Rouge:
			UnloadAnimation(kCO2->MotionList);
			kCO2->MotionList = LoadMTNFile((char*)animName.c_str());
			break;
		case Characters_MechEggman:
		case Characters_MechTails:
			UnloadAnimation(meCO2->MotionList);
			meCO2->MotionList = LoadMTNFile((char*)animName.c_str());
			break;
		}
	}
}

void LoadCoverSkinTex(SkinMenuItem* skin)
{
	if (isLegacy(skin->data.Type))
		return;

	std::string s = GetPakOrPrsTexture(skin->data.FolderPath.c_str(), skin->data.Cover.c_str());

	if (s != "")
	{
		std::string id = std::to_string(skin->data.uniqueID);
		std::string fileName = skin->data.Cover + id;
		const std::string legacyTexPath = resourcedir + fileName + ".prs";
		HelperFunctionsGlobal.ReplaceFile(legacyTexPath.c_str(), s.c_str());
		skin->coverTexlist = LoadCharTextures(fileName.c_str());
	}
}

static void DoSpeedCharsSwap(SkinMod* skin, SonicCharObj2* sCo2, const uint8_t pnum)
{
	JiggleInfo* Jiggle = sCo2->SpineJiggle;

	if (Jiggle)
	{
		Delete_Jiggle(Jiggle);
		sCo2->SpineJiggle = 0;
	}

	auto extraData = skin->Extra;
	const uint8_t charID2 = sCo2->base.CharID2;
	std::string mdlName = extraData.mdlName + (std::string)".PRS";
	const bool Legacy = isLegacy(skin->Type);
	const std::string folderPath = skin->FolderPath;

	if (DirectoryExists(folderPath) || Legacy)
	{
		unReplaceFiles(charID2);

		if (Legacy == false)
			SkinReplaceFiles(skin->FolderPath.c_str(), charID2);

		//Replace Model
		ReleaseMDLFile(sCo2->ModelList);
		sCo2->ModelList = LoadMDLFile((char*)mdlName.c_str());

		if (isAlt(skin->Type))
			sCo2->base.Costume = 1;
		else
			sCo2->base.Costume = 0;

		//Replace Textures
		FreeTexList(sCo2->TextureList);
		FreeMemory((int*)sCo2->TextureList, (char*)"..\\..\\src\\figure\\sonic\\sonic.c", 6272);
		sCo2->TextureList = LoadCharTextures(extraData.texName.c_str());
		LoadExtraTextures(&extraData, pnum, charID2);

		const std::string gdPCMod = folderPath + "\\gd_PC\\";
		bool hadCustomAnim = HasCustomAnims(&currentSkin[pnum][charID2].Extra, currentSkin[pnum][charID2].FolderPath.c_str());
		ReplaceAnimations(&extraData, gdPCMod.c_str(), pnum, hadCustomAnim);
	}


	if (skin->DisableJiggle == false || Legacy)
	{
		if (charID2 == Characters_Sonic)
			LoadSonicJiggle(sCo2);
		else if (charID2 == Characters_Shadow)
			LoadShadowJiggle(sCo2);
		else if (charID2 == Characters_Amy)
			LoadAmyJiggle(sCo2);
	}

	currentSkin[pnum][charID2] = *skin;
}

static void DoMilesSwap(SkinMod* skin, TailsCharObj2New* mCo2, const uint8_t pnum)
{
	JiggleInfo* Jiggle = mCo2->tailJiggle0;

	if (Jiggle)
	{
		Delete_Jiggle(Jiggle);
		mCo2->tailJiggle0 = 0;
	}

	Jiggle = mCo2->tailJiggle1;

	if (Jiggle)
	{
		Delete_Jiggle(Jiggle);
		mCo2->tailJiggle1 = 0;
	}

	auto extraData = skin->Extra;
	const uint8_t charID2 = mCo2->base.CharID2;
	std::string mdlName = extraData.mdlName + (std::string)".PRS";
	const bool Legacy = isLegacy(skin->Type);
	const std::string folderPath = skin->FolderPath;

	if (DirectoryExists(folderPath) || Legacy)
	{
		unReplaceFiles(charID2);

		if (Legacy == false)
			SkinReplaceFiles(skin->FolderPath.c_str(), charID2);

		//Replace Model
		ReleaseMDLFile(mCo2->ModelList);
		mCo2->ModelList = LoadMDLFile((char*)mdlName.c_str());

		//Replace Textures
		FreeTexList(mCo2->TextureList);
		FreeMemory((int*)mCo2->TextureList, (char*)"..\\..\\src\\figure\\miles\\miles.c", 2299);
		mCo2->TextureList = LoadCharTextures(extraData.texName.c_str());
		LoadExtraTextures(&extraData, pnum, charID2);

		const std::string gdPCMod = folderPath + "\\gd_PC\\";
		bool hadCustomAnim = HasCustomAnims(&currentSkin[pnum][charID2].Extra, currentSkin[pnum][charID2].FolderPath.c_str());
		ReplaceAnimations(&extraData, gdPCMod.c_str(), pnum, hadCustomAnim);
	}

	if (skin->DisableJiggle == false)
		LoadMilesJiggle(mCo2);

	currentSkin[pnum][charID2] = *skin;
}

static void DoEggmanSwap(SkinMod* skin, EggmanCharObj2* eCo2, const uint8_t pnum)
{
	auto extraData = skin->Extra;
	const uint8_t charID2 = eCo2->base.CharID2;
	std::string mdlName = extraData.mdlName + (std::string)".PRS";
	const bool Legacy = isLegacy(skin->Type);
	const std::string folderPath = skin->FolderPath;

	if (DirectoryExists(folderPath) || Legacy)
	{
		unReplaceFiles(charID2);

		if (Legacy == false)
			SkinReplaceFiles(skin->FolderPath.c_str(), charID2);

		//Replace Model
		ReleaseMDLFile(eCo2->ModelList);
		eCo2->ModelList = LoadMDLFile((char*)mdlName.c_str());

		//Replace Textures
		FreeTexList(eCo2->TextureList);
		FreeMemory((int*)eCo2->TextureList, (char*)"..\\..\\src\\figure\\eggman\\eggman.c", 2079);
		eCo2->TextureList = LoadCharTextures(extraData.texName.c_str());
		LoadExtraTextures(&extraData, pnum, charID2);

		const std::string gdPCMod = folderPath + "\\gd_PC\\";
		bool hadCustomAnim = HasCustomAnims(&currentSkin[pnum][charID2].Extra, currentSkin[pnum][charID2].FolderPath.c_str());
		ReplaceAnimations(&extraData, gdPCMod.c_str(), pnum, hadCustomAnim);
	}

	currentSkin[pnum][charID2] = *skin;
}

static void DoKnuxRougeSwap(SkinMod* skin, KnucklesCharObj2* kCo2, const uint8_t pnum)
{
	JiggleInfo* Jiggle = kCo2->HeadJiggle;

	if (Jiggle)
	{
		Delete_Jiggle(Jiggle);
		kCo2->HeadJiggle = 0;
	}

	Jiggle = kCo2->UpperTorsoJiggle;

	if (Jiggle)
	{
		Delete_Jiggle(Jiggle);
		kCo2->UpperTorsoJiggle = 0;
	}

	Jiggle = kCo2->LowerTorsoJiggle;

	if (Jiggle)
	{
		Delete_Jiggle(Jiggle);
		kCo2->LowerTorsoJiggle = 0;
	}

	auto extraData = skin->Extra;
	const uint8_t charID2 = kCo2->base.CharID2;
	std::string mdlName = extraData.mdlName + (std::string)".PRS";
	const bool Legacy = isLegacy(skin->Type);
	const std::string folderPath = skin->FolderPath;

	if (DirectoryExists(folderPath) || Legacy)
	{
		unReplaceFiles(kCo2->base.CharID2);

		if (Legacy == false)
			SkinReplaceFiles(skin->FolderPath.c_str(), charID2);

		//Replace Model
		ReleaseMDLFile(kCo2->ModelList);
		kCo2->ModelList = LoadMDLFile((char*)mdlName.c_str());

		if (isAlt(skin->Type))
			kCo2->base.Costume = 1;
		else
			kCo2->base.Costume = 0;

		//Replace Textures
		FreeTexList(kCo2->TextureList);
		FreeMemory((int*)kCo2->TextureList, (char*)"..\\..\\src\\figure\\knuckles\\knuckles.c", 5464);
		kCo2->TextureList = LoadCharTextures(extraData.texName.c_str());
		LoadExtraTextures(&extraData, pnum, charID2);

		const std::string gdPCMod = folderPath + "\\gd_PC\\";
		bool hadCustomAnim = HasCustomAnims(&currentSkin[pnum][charID2].Extra, currentSkin[pnum][charID2].FolderPath.c_str());
		ReplaceAnimations(&extraData, gdPCMod.c_str(), pnum, hadCustomAnim);
		InitCharacterSound();
	}

	if (skin->DisableJiggle == false || Legacy)
	{
		if (charID2 == Characters_Knuckles)
			LoadKnuxJiggle(kCo2);
		else if (charID2 == Characters_Rouge)
			LoadRougeJiggle(kCo2, (skin->Type == Alt || skin->Type == LegacyAlt));
		else if (charID2 == Characters_Tikal)
			LoadTikalJiggle(kCo2);
	}

	currentSkin[pnum][charID2] = *skin;
}

static void DoMechSwap(SkinMod* skin, MechEggmanCharObj2* meCo2, const uint8_t pnum)
{
	auto extraData = skin->Extra;
	const uint8_t charID2 = meCo2->base.CharID2;
	std::string mdlName = extraData.mdlName + (std::string)".PRS";
	const bool Legacy = isLegacy(skin->Type);
	const std::string folderPath = skin->FolderPath;

	if (DirectoryExists(folderPath) || Legacy)
	{
		unReplaceFiles(charID2);

		if (Legacy == false)
			SkinReplaceFiles(skin->FolderPath.c_str(), charID2);

		//Replace Model
		ReleaseMDLFile(meCo2->ModelList);
		meCo2->ModelList = LoadMDLFile((char*)mdlName.c_str());

		if (isAlt(skin->Type))
			meCo2->base.Costume = 1;
		else
			meCo2->base.Costume = 0;

		//Replace Textures
		FreeTexList(meCo2->TextureList);
		FreeMemory((int*)meCo2->TextureList, (char*)"..\\..\\src\\figure\\ewalker\\ewalker.c", 3555);
		meCo2->TextureList = LoadCharTextures(extraData.texName.c_str());
		FreeMemory((int*)meCo2->CommonTextureList, (char*)"..\\..\\src\\figure\\ewalker\\ewalker.c", 3558);
		meCo2->CommonTextureList = LoadCharTextures("WALKTEX");
		LoadExtraTextures(&extraData, pnum, charID2);

		const std::string gdPCMod = folderPath + "\\gd_PC\\";
		bool hadCustomAnim = HasCustomAnims(&currentSkin[pnum][charID2].Extra, currentSkin[pnum][charID2].FolderPath.c_str());
		ReplaceAnimations(&extraData, gdPCMod.c_str(), pnum, hadCustomAnim);
	}

	currentSkin[pnum][charID2] = *skin;
}

static void DoSuperSwap(SkinMod* skin, SuperSonicCharObj2* ssCo2, const uint8_t pnum)
{
	JiggleInfo* Jiggle = ssCo2->SpineJiggle;

	if (Jiggle)
	{
		Delete_Jiggle(Jiggle);
		ssCo2->SpineJiggle = 0;
	}

	auto extraData = skin->Extra;
	const uint8_t charID2 = ssCo2->base.CharID2;
	std::string mdlName = extraData.mdlName + (std::string)".PRS";
	const bool Legacy = isLegacy(skin->Type);
	const std::string folderPath = skin->FolderPath;

	if (DirectoryExists(folderPath) || Legacy)
	{
		unReplaceFiles(charID2);

		if (Legacy == false)
			SkinReplaceFiles(skin->FolderPath.c_str(), charID2);

		//Replace Model
		ReleaseMDLFile(ssCo2->ModelList);
		ssCo2->ModelList = LoadMDLFile((char*)mdlName.c_str());

		//Replace Textures
		FreeTexList(ssCo2->TextureList);
		FreeMemory((int*)ssCo2->TextureList, (char*)"..\\..\\src\\figure\\miles\\miles.c", 2299);
		ssCo2->TextureList = LoadCharTextures(extraData.texName.c_str());
		LoadExtraTextures(&extraData, pnum, charID2);

		const std::string gdPCMod = folderPath + "\\gd_PC\\";
		bool hadCustomAnim = HasCustomAnims(&currentSkin[pnum][charID2].Extra, currentSkin[pnum][charID2].FolderPath.c_str());
		ReplaceAnimations(&extraData, gdPCMod.c_str(), pnum, hadCustomAnim);
	}

	if (skin->DisableJiggle == false || Legacy)
	{
		if (charID2 == Characters_SuperSonic)
			LoadSuperSonicJiggle(ssCo2);
		else if (charID2 == Characters_SuperShadow)
			LoadSuperShadowJiggle(ssCo2);

	}
	

	currentSkin[pnum][charID2] = *skin;
}


void InitEyesTrack(uint8_t charID2, uint8_t pnum)
{
	switch (charID2)
	{
	case Characters_Sonic:
		SonicEyesArray[0] = CharacterModels[3].Model;
		SonicEyesArray[1] = CharacterModels[4].Model;
		SonicEyesArray[2] = CharacterModels[5].Model;
		LoadEyesTrack(pnum, SonicEyesArray);
		break;
	case Characters_Shadow:
		ShadowEyesArray[0] = CharacterModels[68].Model;
		ShadowEyesArray[1] = CharacterModels[69].Model;
		ShadowEyesArray[2] = CharacterModels[70].Model;
		LoadEyesTrack(pnum, ShadowEyesArray);
		break;
	case Characters_Tails:
		MilesEyesArray[0] = CharacterModels[211].Model;
		MilesEyesArray[1] = CharacterModels[212].Model;
		MilesEyesArray[2] = CharacterModels[213].Model;
		LoadEyesTrack(pnum, MilesEyesArray);
		break;
	case Characters_Knuckles:
		KnuxEyesArray[0] = CharacterModels[145].Model;
		KnuxEyesArray[1] = CharacterModels[146].Model;
		KnuxEyesArray[2] = CharacterModels[147].Model;
		LoadEyesTrack(pnum, KnuxEyesArray);
		break;
	case Characters_Rouge:
		RougeEyesArray[0] = CharacterModels[175].Model;
		RougeEyesArray[1] = CharacterModels[176].Model;
		RougeEyesArray[2] = CharacterModels[177].Model;
		LoadEyesTrack(pnum, RougeEyesArray);
		break;
	case Characters_Tikal:
		TikalEyesArray[0] = CharacterModels[486].Model;
		TikalEyesArray[1] = CharacterModels[487].Model;
		TikalEyesArray[2] = CharacterModels[488].Model;
		LoadEyesTrack(pnum, TikalEyesArray);
		break;
	case Characters_Amy:
		AmyEyesArray[0] = CharacterModels[398].Model;
		AmyEyesArray[1] = CharacterModels[399].Model;
		AmyEyesArray[2] = CharacterModels[400].Model;
		LoadEyesTrack(pnum, AmyEyesArray);
		break;
	case Characters_MetalSonic:
		MSEyesArray[0] = CharacterModels[421].Model;
		MSEyesArray[1] = CharacterModels[422].Model;
		MSEyesArray[2] = CharacterModels[423].Model;
		LoadEyesTrack(pnum, MSEyesArray);
		break;
	case Characters_SuperSonic:
		SuperSonicEyesArray[0] = CharacterModels[331].Model;
		SuperSonicEyesArray[1] = CharacterModels[332].Model;
		SuperSonicEyesArray[2] = CharacterModels[333].Model;
		LoadEyesTrack(pnum, SuperSonicEyesArray);
		break;
	case Characters_SuperShadow:
		SuperShadowEyesArray[0] = CharacterModels[358].Model;
		SuperShadowEyesArray[1] = CharacterModels[359].Model;
		SuperShadowEyesArray[2] = CharacterModels[360].Model;
		LoadEyesTrack(pnum, SuperShadowEyesArray);
		break;
	}

}

void SwapSkin(const uint8_t pnum)
{
	ModelIndex* mdl = nullptr;
	void* spePwk = MainCharacter[pnum]->Data2.Undefined;
	auto sCO2 = (SonicCharObj2*)spePwk;
	auto mCO2 = (TailsCharObj2*)spePwk;
	auto eCO2 = (EggmanCharObj2*)spePwk;
	auto kCO2 = (KnucklesCharObj2*)spePwk;
	auto meCO2 = (MechEggmanCharObj2*)spePwk;
	auto SSCo2 = (SuperSonicCharObj2*)spePwk;

	CharInfo* costume = nullptr;
	SkinMenuItem* skin = nullptr;

	switch (MainCharObj2[pnum]->CharID)
	{
	case Characters_Sonic:
	case Characters_Shadow:
		mdl = sCO2->ModelList;
		skin = GetSelectedSkin(pnum);
		if (skin && mdl)
			DoSpeedCharsSwap(&skin->data, sCO2, pnum);
		break;
	case Characters_Tails:
		mdl = mCO2->ModelList;
		skin = GetSelectedSkin(pnum);
		if (skin && mdl)
			DoMilesSwap(&skin->data, (TailsCharObj2New*)mCO2, pnum);
		break;
	case Characters_Eggman:
		mdl = eCO2->ModelList;
		skin = GetSelectedSkin(pnum);
		if (skin && mdl)
			DoEggmanSwap(&skin->data, eCO2, pnum);
		break;
	case Characters_Knuckles:
	case Characters_Rouge:
		mdl = kCO2->ModelList;
		skin = GetSelectedSkin(pnum);
		if (skin && mdl)
			DoKnuxRougeSwap(&skin->data, kCO2, pnum);
		break;
	case Characters_MechTails:
	case Characters_MechEggman:
		mdl = meCO2->ModelList;
		skin = GetSelectedSkin(pnum);
		if (skin && mdl)
			DoMechSwap(&skin->data, meCO2, pnum);
		break;
	case Characters_SuperSonic:
	case Characters_SuperShadow:
		mdl = SSCo2->ModelList;
		skin = GetSelectedSkin(pnum);
		if (skin && mdl)
			DoSuperSwap(&skin->data, SSCo2, pnum);
		break;
	}

	DeleteHomingAttackEffect = false;
}


static void FillCharInfo(SkinMod* mod)
{
	const bool Alt = isAlt(mod->Type);
	switch (mod->Character)
	{
	case Characters_Sonic:
		mod->Extra = Alt ? SonicLegacyInfo[1] : SonicLegacyInfo[0];
		break;
	case Characters_Shadow:
		mod->Extra = Alt ? ShadowLegacyInfo[1] : ShadowLegacyInfo[0];
		break;
	case Characters_Tails:
		mod->Extra = MilesLegacyInfo;
		break;
	case Characters_Eggman:
		mod->Extra = EggmanLegacyInfo;
		break;
	case Characters_Knuckles:
		mod->Extra = Alt ? KnuxLegacyInfo[1] : KnuxLegacyInfo[0];
		break;
	case Characters_Rouge:
		mod->Extra = Alt ? RougeLegacyInfo[1] : RougeLegacyInfo[0];
		break;
	case Characters_MechTails:
		mod->Extra = Alt ? MechTailsLegacyInfo[1] : MechTailsLegacyInfo[0];
		break;
	case Characters_MechEggman:
		mod->Extra = Alt ? MechEggmanLegacyInfo[1] : MechEggmanLegacyInfo[0];
		break;
	case Characters_Amy:
		mod->Extra = AmyLegacyInfo;
		break;
	case Characters_MetalSonic:
		mod->Extra = MSLegacyInfo;
		break;
	case Characters_Tikal:
		mod->Extra = TikalLegacyInfo;
		break;
	case Characters_Chaos:
		mod->Extra = ChaosLegacyInfo;
		break;
	case Characters_SuperSonic:
		mod->Extra = SSLegacyInfo;
		break;
	case Characters_SuperShadow:
		mod->Extra = SSHLegacyInfo;
		break;
	}
}

void ScanSuperFormSubDirectory(std::string gdPCMod, std::vector<SkinMod>& list, SkinMod* info)
{
	auto charID2 = info->Character;
	if (charID2 == Characters_Sonic)
	{
		std::string SSFolder = gdPCMod + SSLegacyInfo.mdlName;
		if (DirectoryExists(normalizePath(SSFolder.c_str())))
		{
			SkinMod info2{};
			info2 = *info;
			info2.Character = Characters_SuperSonic;
			info2.Name = "Super " + info->Name;
			info2.Cover = "CoverSS";
			info2.uniqueID++;
			FillCharInfo(&info2);
			list.push_back(info2);
		}
	}
	else if (charID2 == Characters_Shadow)
	{
		std::string SSHFolder = gdPCMod + SSHLegacyInfo.mdlName;
		if (DirectoryExists(normalizePath(SSHFolder.c_str())))
		{
			SkinMod info2{};
			info2 = *info;
			info2.Character = Characters_SuperShadow;
			info2.Name = "Super " + info->Name;
			info2.Cover = "CoverSSH";
			info2.uniqueID++;
			FillCharInfo(&info2);
			list.push_back(info2);
		}
	}
}

void ScanAltSubDirectory(std::string gdPCMod, std::vector<SkinMod>& list, SkinMod* info)
{
	std::string Folder = gdPCMod;

	switch (info->Character)
	{
	case Characters_Sonic:
		Folder += SonicLegacyInfo[1].mdlName;
		break;
	case Characters_Shadow:
		Folder += ShadowLegacyInfo[1].mdlName;
		break;
	case Characters_MechTails:
		Folder += MechTailsLegacyInfo[1].mdlName;
		break;
	case Characters_MechEggman:
		Folder += MechEggmanLegacyInfo[1].mdlName;
		break;
	case Characters_Knuckles:
		Folder += KnuxLegacyInfo[1].mdlName;
		break;
	case Characters_Rouge:
		Folder += RougeLegacyInfo[1].mdlName;
		break;
	}

	if (DirectoryExists(normalizePath(Folder.c_str())))
	{
		SkinMod info2{};
		info2 = *info;
		info2.Type = Alt;
		info2.Name += " (Alt)";
		info2.Cover = "CoverAlt";
		info2.uniqueID++;
		FillCharInfo(&info2);
		list.push_back(info2);
	}
}


void ScanMechSubDirectory(std::string gdPCMod, std::vector<SkinMod>& list, SkinMod* info)
{
	auto charID2 = info->Character;
	if (charID2 == Characters_Tails)
	{
		std::string MechFolder = gdPCMod + MechTailsLegacyInfo[0].mdlName;
		if (DirectoryExists(normalizePath(MechFolder.c_str())))
		{
			SkinMod info2{};
			info2 = *info;
			info2.Character = Characters_MechTails;
			info2.Name = "Mech " + info->Name;
			info2.Cover = "mechT";
			info2.uniqueID++;
			FillCharInfo(&info2);
			list.push_back(info2);
			ScanAltSubDirectory(gdPCMod, list, &info2);
		}
	}
	else if (charID2 == Characters_Eggman)
	{
		std::string SSHFolder = gdPCMod + SSHLegacyInfo.mdlName;
		if (DirectoryExists(normalizePath(SSHFolder.c_str())))
		{
			SkinMod info2{};
			info2 = *info;
			info2.Character = Characters_MechEggman;
			info2.Name = "Mech " + info->Name;
			info2.Cover = "mechE";
			info2.uniqueID++;
			FillCharInfo(&info2);
			list.push_back(info2);
			ScanAltSubDirectory(gdPCMod, list, &info2);
		}
	}
}



void ScanDirectoryForIniFile(std::string srcPath, std::vector<SkinMod>& list)
{
	srcPath = normalizePath(srcPath.c_str());
	WIN32_FIND_DATAA data;
	char path[MAX_PATH];
	snprintf(path, sizeof(path), "%s\\*", srcPath.c_str());
	HANDLE hFind = FindFirstFileA(path, &data);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		// No files found.
		return;
	}

	do
	{
		if (data.cFileName[0] == '.')
		{
			continue;
		}

		//check if there is subfolder...
		if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// Recursively scan this directory.
			const std::string newSrcPath = srcPath + "\\" + std::string(data.cFileName);
			ScanDirectoryForIniFile(newSrcPath, list); //restart the scan in the subfolder
			continue;
		}

		const std::string inipath = std::string(srcPath) + "\\skin.ini";

		if (FileExists(inipath))
		{
			const IniFile* skin = new IniFile(inipath);

			std::string s = skin->getString("", "Character", "");

			if (s == "")
			{
				delete skin;
				break;
			}

			toLowercase(s);
			SkinMod info{};
			info.Character = (Characters)getCharacterValue(s);
			const std::string id = std::to_string((uint16_t)skinList.size() + 1);
			info.Name = skin->getString("", "Name", "Skin ID " + id);
			info.Author = skin->getString("", "Author", "Unknown");
			info.Cover = skin->getString("", "Cover", "Cover");
			info.Description = skin->getString("", "Description", "");
			info.DisableJiggle = skin->getBool("", "DisableJiggle", false);

			FillCharInfo(&info);

			info.Extra.mdlName = skin->getString("Extra", "Model", info.Extra.mdlName);
			info.Extra.texName = skin->getString("Extra", "Texture", info.Extra.texName);
			info.Extra.animName = skin->getString("Extra", "Anim", info.Extra.animName);

			info.Type = (SkinType)skin->getInt("Extra", "Alt", Mod);

			std::filesystem::path pathObj(inipath);

			info.FolderPath = normalizePath(pathObj.parent_path().string().c_str());
			info.uniqueID = (uint16_t)skinList.size() + 1;
			list.push_back(info);

			const std::string gdPCMod = info.FolderPath + "\\gd_PC\\";

			ScanSuperFormSubDirectory(gdPCMod, list, &info);
			ScanMechSubDirectory(gdPCMod, list, &info);
			ScanAltSubDirectory(gdPCMod, list, &info);
			delete skin;
			break;
		}

	} while (FindNextFileA(hFind, &data) != 0);

	FindClose(hFind);
}


static void AddLegacySkin()
{
	for (uint8_t i = 0; i < LengthOfArray(SonicLegacy); i++)
		skinList.push_back(SonicLegacy[i]);

	for (uint8_t i = 0; i < LengthOfArray(ShadowLegacy); i++)
		skinList.push_back(ShadowLegacy[i]);

	skinList.push_back(MilesLegacy);
	skinList.push_back(EggmanLegacy);

	for (uint8_t i = 0; i < LengthOfArray(KnuxLegacy); i++)
		skinList.push_back(KnuxLegacy[i]);

	for (uint8_t i = 0; i < LengthOfArray(RougeLegacy); i++)
		skinList.push_back(RougeLegacy[i]);

	for (uint8_t i = 0; i < LengthOfArray(MechTailsLegacy); i++)
		skinList.push_back(MechTailsLegacy[i]);

	for (uint8_t i = 0; i < LengthOfArray(MechEggmanLegacy); i++)
		skinList.push_back(MechEggmanLegacy[i]);

	skinList.push_back(AmyLegacy);
	skinList.push_back(MSLegacy);
	skinList.push_back(TikalLegacy);
	skinList.push_back(ChaosLegacy);
	skinList.push_back(SSLegacy);
	skinList.push_back(SSHLegacy);

	for (uint16_t i = 0; i < skinList.size(); i++)
		skinList[i].uniqueID = i;
}

void initSkinList(const char* path)
{
	AddLegacySkin();
	ScanDirectoryForIniFile(path + (std::string)"\\skins", skinList);

	for (uint8_t i = 0; i < PMax; i++)
	{
		for (uint8_t j = 0; j < CharMax; j++)
		{
			Load(i, j);
		}
	}
}

