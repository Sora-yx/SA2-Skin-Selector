#pragma once

#pragma pack(push, 1)

struct SkinMenuItem
{
	SkinMod data;
	NJS_POINT2 pos{ 0 };
	bool isSelected = false;
	NJS_TEXLIST* coverTexlist = nullptr;
	std::string text = "";
};

struct SkinMenuCursor
{
	NJS_POINT2 curPos{ 0 };
	uint16_t index = 0;
	uint8_t curRow = 0;
	uint8_t curColumn = 0;
	uint8_t curPage = 0;
	SkinMenuItem* currentItem = nullptr;
};


struct SkinMenuData
{
	uint8_t mode = 0;
	Characters currentCharacter = Characters_Sonic;
	uint8_t rowMax = 0;
	uint8_t columnMax = 0;
	uint8_t pageMax = 0;
	NJS_POINT2 pos;
	SkinMenuItem* items;
	uint16_t itemCount = 0;
	uint8_t itemMaxPerPage = 0;
	uint8_t itemsOnPage = 0;
	NJS_POINT2 itemPos[99];
	SkinMenuCursor cursor;
};

void InitMenuHack();
Sint32 GetSkinListIndex(const uint16_t uniqueID);
Uint32 GetCurrentSlotItem(const uint8_t pnum);
SkinMenuItem* GetSelectedItem(const uint8_t pnum);
void LoadCoverSkinTex(SkinMenuItem* skin);
bool isMenuOpenByAPlayer();

std::string GetCharTexturePath(const char* texName, std::string folderPath, std::string legacyTexName);
bool isMenuFullyOpenByAPlayer();
void ClearMenuData(const uint8_t i);

#pragma pack(pop)