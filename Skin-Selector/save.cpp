#include "pch.h"
#include "save.h"
#include "menu.h"
#include <FileSystem.h>
#include <algorithm>

TaskHook SonicDelete_t(Sonic_Delete);
TaskHook MilesDelete_t(Tails_Delete);
TaskHook EggmanDelete_t(Eggman_Delete);
TaskHook KnuxDelete_t(Knuckles_Delete);
TaskHook MechDelete_t(MechEggman_Delete);

SkinMod* savedSkin[PMax][CharMax] = { nullptr };

static void LoadSavedSkin(const uint8_t pnum, const uint8_t charID2)
{
	currentSkin[pnum][charID2] = *savedSkin[pnum][charID2];
	SkinReplaceFiles(currentSkin[pnum][charID2].FolderPath.c_str(), charID2);
}

void Save(const uint8_t pnum, const uint8_t charID2)
{
	const std::string inipath = modPath + "\\skins\\savedata\\" + "Player" + std::to_string(pnum) + ".ini";
	const std::string charIDS = std::to_string(charID2);
	IniFile* skin = new IniFile(inipath);

	IniGroup* group = skin->createGroup(charIDS);
	group->setString("Name", currentSkin[pnum][charID2].Name.c_str());
	group->setString("FolderPath", currentSkin[pnum][charID2].FolderPath.c_str());
	skin->save(inipath);
	delete skin;

}

static SkinMod* GetSavedSkin(uint8_t charID2, const char* folderPath)
{
	for (uint16_t i = 0; i < skinList.size(); i++)
	{
		if (skinList[i].Character == charID2 && skinList[i].FolderPath == folderPath)
		{
			return &skinList[i];
		}
	}

	return nullptr;
}

bool Load(const uint8_t pnum, const uint8_t charID2)
{
	const std::string inipath = modPath + "\\skins\\savedata\\" + "Player" + std::to_string(pnum) + ".ini";

	if (FileExists(inipath))
	{
		const IniFile* skin = new IniFile(inipath);
		const std::string charIDS = std::to_string(charID2);
		const std::string skinFolderPath = skin->getString(charIDS, "FolderPath");

		delete skin;

		if (DirectoryExists(skinFolderPath) && FileExists(skinFolderPath + "\\skin.ini"))
		{
			savedSkin[pnum][charID2] = GetSavedSkin(charID2, skinFolderPath.c_str());
			LoadSavedSkin(pnum, charID2);
			return true;
		}
	}

	return false;
}

void SonicDelete_r(ObjectMaster* obj)
{
	SonicCharObj2* sco2 = (SonicCharObj2*)obj->Data2.Undefined;
	Save(sco2->base.PlayerNum, sco2->base.CharID2);
	SonicDelete_t.Original(obj);
}

void MilesDelete_r(ObjectMaster* obj)
{
	auto co2 = (TailsCharObj2*)obj->Data2.Undefined;
	Save(co2->base.PlayerNum, co2->base.CharID2);
	MilesDelete_t.Original(obj);
}

void EggmanDelete_r(ObjectMaster* obj)
{
	auto co2 = (EggmanCharObj2*)obj->Data2.Undefined;
	Save(co2->base.PlayerNum, co2->base.CharID2);
	EggmanDelete_t.Original(obj);
}

void KnuxDelete_r(ObjectMaster* obj)
{
	auto co2 = (KnucklesCharObj2*)obj->Data2.Undefined;
	Save(co2->base.PlayerNum, co2->base.CharID2);
	KnuxDelete_t.Original(obj);
}

void MechDelete_r(ObjectMaster* obj)
{
	auto co2 = (MechEggmanCharObj2*)obj->Data2.Undefined;
	Save(co2->base.PlayerNum, co2->base.CharID2);
	MechDelete_t.Original(obj);
}

void initSave()
{
	SonicDelete_t.Hook(SonicDelete_r);
	MilesDelete_t.Hook(MilesDelete_r);
	EggmanDelete_t.Hook(EggmanDelete_r);
	KnuxDelete_t.Hook(KnuxDelete_r);
	MechDelete_t.Hook(MechDelete_r);
}