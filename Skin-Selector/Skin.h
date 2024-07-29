#pragma once

#pragma pack(push, 1)
struct CharFileInfo
{
	std::string mdlName = "";
	std::string texName = "";
	std::string animName = "";
	std::string effTexName = "";
	std::string lifeIconTexName = "";
	std::string oneUpTexName = "";
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
	CharFileInfo Extra;
};

void initSkinList(const char* path);
extern std::vector<SkinMod> skinList;
/**pnum / charID2*/
extern SkinMod currentSkin[PMax][CharMax];
CharFileInfo* GetCostumeList(const uint8_t pnum);
void SwapSkin(const uint8_t pnum);
bool isLegacy(SkinType type);
bool isAlt(SkinType type);
void InitEyesTrack(uint8_t charID2, uint8_t pnum);
void SkinReplaceFiles(const char* folderPath, const uint8_t charID2);

extern bool hdGUI;

#pragma pack(pop)