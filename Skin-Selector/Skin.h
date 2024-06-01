#pragma once


struct CharInfo
{
	const char* mdlName;
	const char* texName;
	const char* animName;
	const char* effTexName;
	const char* lifeIconTexName;
	const char* oneUpTexName;
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
	Characters Character;
	std::string Name;
	std::string Author;
	std::string Description;
	std::string Cover;
	std::string FolderPath;
	uint16_t uniqueID;
	SkinType Type;
	bool JiggleDisabled = false;
	CharInfo Extra;
};

void initSkinList(const char* path);
extern std::vector<SkinMod> skinList;
extern SkinMod currentSkin[];
CharInfo* GetCostumeList(const uint8_t pnum);
void SwapSkin(const uint8_t pnum);