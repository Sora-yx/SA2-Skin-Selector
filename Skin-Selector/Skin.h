#pragma once


struct CharInfo
{
	const char* mdlName = NULL;
	const char* texName = NULL;
	const char* animName = NULL;
	const char* effTexName = NULL;
	const char* lifeIconTexName = NULL;
	const char* oneUpTexName = NULL;
};


enum SkinType
{
	Mod,
	Alt,
	Legacy,
	LegacyAlt,
};


struct SkinMod
{
	Characters Character = Characters_Sonic;
	std::string Name;
	std::string Author;
	std::string Description;
	std::string Cover;
	std::string FolderPath;
	uint16_t uniqueID;
	SkinType Type = Mod;
	bool DisableJiggle = false;
	CharInfo Extra;
};

void initSkinList(const char* path);
extern std::vector<SkinMod> skinList;
extern SkinMod currentSkin[PMax][CharMax];
CharInfo* GetCostumeList(const uint8_t pnum);
void SwapSkin(const uint8_t pnum);
bool isLegacy(SkinType type);
void InitEyesTrack(uint8_t charID2, uint8_t pnum);
void SkinReplaceFiles(const char* folderPath, const uint8_t charID2);

extern bool hdGUI;