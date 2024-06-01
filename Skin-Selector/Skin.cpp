#include "pch.h"
#include <iostream>
#include <filesystem>
#include "FileSystem.h"
#include "model.h"
#include "menu.h"

std::vector<SkinMod> skinList;
SkinMod currentSkin[PMax];
const std::string resourcedir = "resource\\gd_pc\\";

CharInfo SonicLegacyInfo[] =
{
	{ "SONICMDL", "SONICTEX", "SONICMTN", "s_efftex", "zanki_sonic", "itemp_1up"},
	{ "SONIC1MDL", "SONIC1TEX", "SONICMTN", "s_efftex", "zanki_sonic", "itemp_1up"},
	{NULL},
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
	{NULL},
};

SkinMod ShadowLegacy[] =
{
	{ Characters_Shadow, "Shadow (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, ShadowLegacyInfo[0]},
	{ Characters_Shadow, "Shadow (Race Costume)", "Sonic Team", "Desc", "", "", 1, LegacyAlt, false, ShadowLegacyInfo[1] },
};

CharInfo MilesLegacyInfo[] =
{
	{ "MILESMDL", "MILESTEX", "MILESMTN", "", "zanki_tails", "itemp_1up3"},
	{NULL},
};


SkinMod MilesLegacy = { Characters_Tails, "Tails (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, MilesLegacyInfo[0] };

CharInfo EggmanLegacyInfo[] =
{
	{ "EGGMDL", "EGGTEX", "EGGMTN", "", "zanki_egg1", "itemp_1up6"},
	{NULL},
};

SkinMod EggmanLegacy = { Characters_Eggman, "Eggman (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, EggmanLegacyInfo[0] };

CharInfo KnuxLegacyInfo[] =
{
	{ "KNUCKMDL", "KNUCKTEX", "KNUCKLMTN", "k_efftex", "zanki_knuckle", "itemp_1up2"},
	{ "BKNUCKMDL", "BKNUCKTEX", "KNUCKLMTN", "k_efftex", "zanki_knuckle", "itemp_1up2"},
	{NULL},
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
	{NULL},
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
	{NULL},
};

SkinMod MechTailsLegacy[] =
{
	{ Characters_MechTails, "Mech Tails (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, MechTailsLegacyInfo[0] },
	{ Characters_MechTails, "Mech Tails (Red Tornado)", "Sonic Team", "Desc", "", "", 1, LegacyAlt, false, MechTailsLegacyInfo[1] },
};

CharInfo MechEggmanLegacyInfo[] =
{
	{ "EWALKMDL", "EWALKTEX", "EWALKMTN", "", "zanki_egg1", "itemp_1up3"},
	{ "EWALK2MDL", "EWALK2TEX",  "EWALKMTN", "", "zanki_egg1", "itemp_1up3"},
	{NULL},
};

SkinMod MechEggmanLegacy[] =
{
	{ Characters_MechEggman, "Mech Eggman (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, MechEggmanLegacyInfo[0] },
	{ Characters_MechEggman, "Mech Eggman (Camouflage)", "Sonic Team", "Desc", "", "", 1, Legacy, false, MechEggmanLegacyInfo[1] },
};

CharInfo AmyLegacyInfo[] =
{
	{ "AMYMDL", "AMYTEX", "AMYMTN", "amy_efftex", "zanki_amy", ""},
	{NULL},
};

SkinMod AmyLegacy = { Characters_Amy, "Amy (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, AmyLegacyInfo[0] };

CharInfo MSLegacyInfo[] =
{
	{ "METALSONICMDL", "METALSONICTEX", "METALSONICMTN", "S_EFFTEX", "zanki_metal", ""},
	{NULL},
};

SkinMod MSLegacy = { Characters_MetalSonic, "Metal Sonic (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, MSLegacyInfo[0] };

CharInfo TikalLegacyInfo[] =
{
	{ "TICALMDL", "TICALTEX", "TICALMTN", "k_efftex", "zanki_tical", ""},
	{NULL},
};

SkinMod TikalLegacy = { Characters_Tikal, "Tikal (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, TikalLegacyInfo[0] };


CharInfo ChaosLegacyInfo[] =
{
	{ "CHAOS0MDL", "CHAOS0TEX", "CHAOS0MTN", "c0_efftex", "zanki_chaos0", ""},
	{NULL},
};

SkinMod ChaosLegacy = { Characters_Chaos, "Chaos 0 (Regular)", "Sonic Team", "Desc", "", "", 0, Legacy, false, ChaosLegacyInfo[0] };

CharInfo* GetCostumeList(const uint8_t pnum)
{
	auto p = MainCharObj2[pnum];
	if (!p)
		return nullptr;

	switch (p->CharID2)
	{
	case Characters_Sonic:
		return SonicLegacyInfo;
	case Characters_Shadow:
		return ShadowLegacyInfo;
	case Characters_Tails:
		return MilesLegacyInfo;
	case Characters_Eggman:
		return EggmanLegacyInfo;
	case Characters_Knuckles:
		return KnuxLegacyInfo;
	case Characters_Rouge:
		return RougeLegacyInfo;
	case Characters_MechTails:
		return MechTailsLegacyInfo;
	case Characters_MechEggman:
		return MechEggmanLegacyInfo;
	case Characters_Amy:
		return AmyLegacyInfo;
	case Characters_MetalSonic:
		return MSLegacyInfo;
	case Characters_Tikal:
		return TikalLegacyInfo;
	case Characters_Chaos:
		return ChaosLegacyInfo;
	}

	return nullptr;
}

static const std::unordered_map<std::string, uint8_t> charnamemap = {
	{ "sonic", Characters_Sonic },
	{ "shadow", Characters_Shadow },
	{ "tails", Characters_Tails },
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
	auto it = charnamemap.find(key);
	if (it != charnamemap.end())
	{
		return it->second;
	}
	else
	{
		return Characters_Sonic;
	}
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

static SkinMenuItem* GetCurrentSkin(const uint8_t pnum)
{
	auto skin = GetSelectedItem(pnum);

	if (skin && GetSkinListIndex(skin->data.uniqueID) > 1)
		return skin;

	return nullptr;
}

std::string GetTexturePath(SkinMenuItem* skin, std::string folderPath, std::string legacyTexName)
{
	std::string s = folderPath + "\\gd_PC\\prs\\" + skin->data.Extra.texName;
	s = normalizePath(s.c_str());

	if (FileExists(s))
		return s;

	s = folderPath + "\\gd_PC\\prs\\" + skin->data.Extra.texName + ".PAK";
	s = normalizePath(s.c_str());

	if (FileExists(s))
		return s;

	s = folderPath + "\\gd_PC\\" + skin->data.Extra.texName + ".PRS";

	if (FileExists(s))
		return s;

	//if still not found, assume it's legacy name and PAK
	s = folderPath + "\\gd_PC\\prs\\" + legacyTexName + ".PAK";

	if (FileExists(s))
		return s;

	return "";
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


static void DoSpeedCharsSwap(SkinMenuItem* skin, SonicCharObj2* sCo2, const uint8_t pnum)
{
	auto costume = GetCostumeList(pnum); //get outfit 

	if (!costume)
		return;

	const std::string legacyTexPath = resourcedir + costume[0].texName + ".prs";

	JiggleInfo* Jiggle = sCo2->SpineJiggle;

	if (Jiggle)
	{
		Delete_Jiggle(Jiggle);
		sCo2->SpineJiggle = 0;
	}

	if (skin->data.Type == Legacy || skin->data.Type == LegacyAlt) //if legacy characters from Vanilla game
	{
		HelperFunctionsGlobal.UnreplaceFile(legacyTexPath.c_str());
		FreeTexList(sCo2->TextureList);
		auto altIndex = GetCurrentSlotItem(pnum);
		sCo2->TextureList = LoadCharTextures(costume[altIndex].texName);
		std::string mdlName = costume[altIndex].mdlName + (std::string)".PRS";
		ReleaseMDLFile(sCo2->ModelList);
		sCo2->ModelList = LoadMDLFile((char*)mdlName.c_str());
	}
	else
	{
		const std::string folderPath = skin->data.FolderPath;
		std::string texPath = GetTexturePath(skin, folderPath, costume[0].texName);
		if (DirectoryExists(folderPath) && FileExists(texPath))
		{
			//Replace Textures
			HelperFunctionsGlobal.UnreplaceFile(legacyTexPath.c_str());
			FreeTexList(sCo2->TextureList);
			HelperFunctionsGlobal.ReplaceFile(legacyTexPath.c_str(), texPath.c_str());
			sCo2->TextureList = LoadCharTextures(costume[0].texName);

			//Replace Model
			ReleaseSkinMDLFile(sCo2->ModelList);
			std::string mdlName = costume[0].mdlName + (std::string)".PRS";
			sCo2->ModelList = LoadSkinMdlFile(mdlName.c_str(), folderPath.c_str());
		}
	}

	const uint8_t charID2 = sCo2->base.CharID2;
	if (skin->data.JiggleDisabled == false)
	{
		if (charID2 == Characters_Sonic)
			LoadSonicJiggle(sCo2);
		else if (charID2 == Characters_Shadow)
			LoadShadowJiggle(sCo2);
		else if (charID2 == Characters_Amy)
			LoadAmyJiggle(sCo2);
	}

	currentSkin[pnum] = skin->data;
}

static void DoKnuxRougeSwap(SkinMenuItem* skin, KnucklesCharObj2* kCo2, const uint8_t pnum)
{
	auto costume = GetCostumeList(pnum); //get outfit 

	if (!costume)
		return;

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

	const std::string legacyTexPath = resourcedir + costume[0].texName + ".prs";

	if (skin->data.Type == Legacy || skin->data.Type == LegacyAlt) //if legacy characters from Vanilla game
	{
		HelperFunctionsGlobal.UnreplaceFile(legacyTexPath.c_str());
		FreeTexList(kCo2->TextureList);
		const auto altIndex = GetCurrentSlotItem(pnum);
		kCo2->TextureList = LoadCharTextures(costume[altIndex].texName);
		std::string mdlName = costume[altIndex].mdlName + (std::string)".PRS";
		ReleaseMDLFile(kCo2->ModelList);
		kCo2->ModelList = LoadMDLFile((char*)mdlName.c_str());
	}
	else
	{
		const std::string folderPath = skin->data.FolderPath;
		std::string texPath = GetTexturePath(skin, folderPath, costume[0].texName);
		if (DirectoryExists(folderPath) && FileExists(texPath))
		{
			HelperFunctionsGlobal.UnreplaceFile(legacyTexPath.c_str());
			FreeTexList(kCo2->TextureList);
			HelperFunctionsGlobal.ReplaceFile(legacyTexPath.c_str(), texPath.c_str());
			kCo2->TextureList = LoadCharTextures(costume[0].texName);

			ReleaseSkinMDLFile(kCo2->ModelList);
			std::string mdlName = costume[0].mdlName + (std::string)".PRS";
			kCo2->ModelList = LoadSkinMdlFile(mdlName.c_str(), folderPath.c_str());
		}
	}

	const uint8_t charID2 = kCo2->base.CharID2;
	if (skin->data.JiggleDisabled == false)
	{
		if (charID2 == Characters_Knuckles)
			LoadKnuxJiggle(kCo2);
		else if (charID2 == Characters_Rouge)
			LoadRougeJiggle(kCo2, (skin->data.Type == Alt || skin->data.Type == LegacyAlt));
		else if (charID2 == Characters_Tikal)
			LoadTikalJiggle(kCo2);
	}

	currentSkin[pnum] = skin->data;
}

void SwapSkin(const uint8_t pnum)
{
	ModelIndex* mdl = nullptr;
	void* spePwk = MainCharacter[pnum]->Data2.Undefined;
	SonicCharObj2* sCO2 = (SonicCharObj2*)spePwk;
	TailsCharObj2* mCO2 = (TailsCharObj2*)spePwk;
	EggmanCharObj2* eCO2 = (EggmanCharObj2*)spePwk;
	KnucklesCharObj2* kCO2 = (KnucklesCharObj2*)spePwk;
	MechEggmanCharObj2* meCO2 = (MechEggmanCharObj2*)spePwk;
	SuperSonicCharObj2* SSCo2 = (SuperSonicCharObj2*)spePwk;

	CharInfo* costume = nullptr;
	SkinMenuItem* skin = nullptr;


	switch (MainCharObj2[pnum]->CharID)
	{
	case Characters_Sonic:
	case Characters_Shadow:
		mdl = sCO2->ModelList;
		skin = GetCurrentSkin(pnum);
		skin = GetCurrentSkin(pnum);
		if (skin && mdl)
			DoSpeedCharsSwap(skin, sCO2, pnum);
		break;
	case Characters_Tails:
		mdl = mCO2->ModelList;
		skin = GetCurrentSkin(pnum);
		/*if (skin && mdl && textureList)
			DoMilesSwap(skin, mCO2, pnum);*/
		break;
	case Characters_Eggman:
		mdl = eCO2->ModelList;
		skin = GetCurrentSkin(pnum);
		/**if (skin && mdl)
			DoEggmanSwap(skin, kCO2, pnum);*/
		break;
	case Characters_Knuckles:
	case Characters_Rouge:
		mdl = kCO2->ModelList;
		skin = GetCurrentSkin(pnum);
		if (skin && mdl)
			DoKnuxRougeSwap(skin, kCO2, pnum);
		break;
	case Characters_MechTails:
	case Characters_MechEggman:
		mdl = meCO2->ModelList;
		skin = GetCurrentSkin(pnum);
		/**if (skin && mdl)
			DoMechSwap(skin, meCO2, pnum);*/
		break;
	case Characters_SuperSonic:
	case Characters_SuperShadow:
		mdl = SSCo2->ModelList;
		skin = GetCurrentSkin(pnum);
		/**if (skin && mdl)
			DoSuperSwap(skin, meCO2, pnum);*/
		break;
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

			std::string s = skin->getString("", "Character", "sonic");
			toLowercase(s);
			SkinMod info{};
			info.Character = (Characters)getCharacterValue(s);
			const std::string id = std::to_string(skinList.size() + 1);
			info.Name = skin->getString("", "Name", "Skin ID " + id);
			info.Author = skin->getString("", "Author", "Unknown");
			info.Cover = skin->getString("", "Cover", "");
			info.Description = skin->getString("", "Description", "");
			info.JiggleDisabled = skin->getBool("", "JiggleDisabled", false);

			info.Extra.texName = skin->getString("Extra", "Texture").c_str();
			info.Extra.animName = skin->getString("Extra", "Anim").c_str();
			info.Type = (SkinType)skin->getInt("Extra", "Alt", Mod);
			std::filesystem::path pathObj(inipath);
			
			info.FolderPath = normalizePath(pathObj.parent_path().string().c_str());
			info.uniqueID = skinList.size() + 1;
			list.push_back(info);
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

	for (uint16_t i = 0; i < skinList.size(); i++)
		skinList[i].uniqueID = i;
}

void initSkinList(const char* path)
{
	AddLegacySkin();
	ScanDirectoryForIniFile(path + (std::string)"\\skins", skinList);
}

