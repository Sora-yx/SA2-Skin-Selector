#include "pch.h"
#include "menu.h"
#include <iostream>
#include <filesystem>
#include "FileSystem.h"
#include "input.h"

FunctionHook<void> LoadCharacters_t((intptr_t)LoadCharacters);
FunctionHook<void, int> RunObjectIndex_t(RunObjectIndex);

static NJS_TEXNAME menuTex[25];
static NJS_TEXLIST menuTexlist{ arrayptrandlengthT(menuTex, Uint32) };

const Sint16 charIconX = 59;
const Sint16 charIconY = 59;

task* menuTask[PMax];

enum menuDataE
{
	Closed,
	Init,
	Open,
	ItemSelected,
	Exit,
};


enum texIndexE
{
	texIDAllBG,
	texIDCheckMark,
	texIDCursor,
	texIDUnknownItem,
	texIDSonic,
	texIDShadow,
	texIDMiles,
	texIDEggman,
	texIDKnux,
	texIDRouge,
	texIDTailsM,
	texIDEggmanM,
	texIDAmy,
	texIDMetalSonic,
	texIDNeutralChao,
	texIDDarkChao,
	texIDTikal,
	texIDChaos,
	texIDSkinSelectText,
	texIDSonicAlt,
	texIDShadowAlt,
	texIDKnuxAlt,
	texIDRougeAlt,
	texIDTailsMAlt,
	texIDEggmanMAlt
};

uint8_t getAltTexID(const uint8_t charID)
{
	switch (charID)
	{
	case Characters_Sonic:
		return texIDSonicAlt;
	case Characters_Shadow:
		return texIDShadowAlt;
	case Characters_Knuckles:
		return texIDKnuxAlt;
	case Characters_Rouge:
		return texIDRougeAlt;
	case Characters_MechTails:
		return texIDTailsMAlt;
	case Characters_MechEggman:
		return texIDEggmanMAlt;
	}

	return 0;
}

const Float cursorSize = 82;
static NJS_TEXANIM menuTexAnim[]
{
	{ 400, 300, 0, 0, 0, 0, 0x0FF, 0x0FF, texIDAllBG, 0x0 },
	{ 36 , 36, 0, 0, 0, 0, 0x0FF, 0x0FF, texIDCheckMark, 0x0 },
	{ cursorSize, cursorSize,  cursorSize / 2, cursorSize / 2, 0, 0, 0xFF, 0xFF, texIDCursor, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDUnknownItem, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDSonic, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDShadow, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDMiles, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDEggman, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDKnux, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDRouge, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDTailsM, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDEggmanM, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDAmy, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDMetalSonic, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDNeutralChao, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDDarkChao, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDTikal, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDChaos, 0x0 },
	{ 150, 32, 0, 0, 0, 0, 0xFF, 0xFF, texIDSkinSelectText, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDSonicAlt, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDShadowAlt, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDKnuxAlt, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDRougeAlt, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDTailsMAlt, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDEggmanMAlt, 0x0 },
};

static NJS_SPRITE menuSprite = { { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 0, &menuTexlist, menuTexAnim };

static NJS_TEXANIM menuCustomIconTexAnim =
{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, 0, 0 };


SkinMenuData menu[PMax];

SkinMenuItem* GetSelectedItem(const uint8_t pnum)
{
	return menu[pnum].cursor.currentItem;
}

void PrintDebugValues(uint8_t pnum)
{
	HelperFunctionsGlobal.SetDebugFontSize(22);
	PrintDebugText(NJM_LOCATION(2, 3), "Current Index: %d", menu[pnum].cursor.index);
	PrintDebugText(NJM_LOCATION(2, 4), "Current Page: %d", menu[pnum].cursor.curPage);
	PrintDebugText(NJM_LOCATION(2, 5), "Current Column: %d", menu[pnum].cursor.curColumn);
	PrintDebugText(NJM_LOCATION(2, 6), "Current Row: %d", menu[pnum].cursor.curRow);

	if (menu[pnum].cursor.currentItem)
		PrintDebugText(NJM_LOCATION(2, 7), "Selected Skin: %s", menu[pnum].items[menu[pnum].cursor.index].data.Name.c_str());
}

void calculateTitlePosition(const uint8_t pnum, Float sizeX, Float sizeY, Float* outPosX, Float* outPosY) 
{
	*outPosX = menu[pnum].pos.x + (menuTexAnim[texIDAllBG].sx - sizeX) / 2.0f;
	*outPosY = menu[pnum].pos.y - (sizeY / 2.0f) + 9.0f;
}

void calculateBackgroundPosition(Float sizeX, Float sizeY, Float* bgPosX, Float* bgPosY) 
{
	// Calculate scaling factors
	Float resScaleX = (HorizontalResolution / 640.0f);
	Float resScaleY = (VerticalResolution / 480.0f);

	// Calculate center position in the game's coordinate system
	Float centerX = (HorizontalResolution / 2.0f) / resScaleX;
	Float centerY = (VerticalResolution / 2.0f) / resScaleY;

	// Calculate background position to center it
	*bgPosX = centerX - (sizeX / 2.0f);
	*bgPosY = centerY - (sizeY / 2.0f);
}

Uint32 GetRealMenuItemIndex(const uint8_t pnum)
{
	return menu[pnum].cursor.index + (menu[pnum].cursor.curPage * menu[pnum].itemMaxPerPage);
}

Uint32 GetCurrentSlotItem(const uint8_t pnum)
{
	return (menu[pnum].cursor.curRow * menu[pnum].columnMax) + menu[pnum].cursor.curColumn;
}

Uint32 GetNextIndex(const uint8_t pnum, const uint8_t nextRow, const uint8_t nextColumn)
{
	return (nextRow * menu[pnum].columnMax) + nextColumn;
}

Uint32 GetMaxIndex(const uint8_t pnum)
{
	return menu[pnum].itemCount - 1;
}

void UpdateCursorPos(const uint8_t pnum)
{
	menu[pnum].cursor.index = GetCurrentSlotItem(pnum);
}

static bool isMenuOpenByAnotherPlayer(const uint8_t pnum)
{
	for (uint8_t j = 0; j < PMax; j++)
	{
		if (j == pnum)
			continue;

		if (menu[j].mode != Closed)
			return true;
	}

	return false;
}

static bool isMenuOpenByAPlayer()
{
	for (uint8_t j = 0; j < PMax; j++)
	{
		if (menu[j].mode != Closed)
			return true;
	}

	return false;
}

static bool isCursorOnTop(const uint8_t pnum)
{
	return menu[pnum].cursor.curRow == 0;
}

static bool isCursorAtTheBottom(const uint8_t pnum)
{
	return menu[pnum].cursor.curRow == menu[pnum].rowMax - 1;
}

static void GoToLastItem(const int lastSlot, const uint8_t pnum)
{
	menu[pnum].cursor.curRow = lastSlot / menu[pnum].columnMax; // Dividing by columnMax to get the correct row
	menu[pnum].cursor.curColumn = lastSlot % menu[pnum].columnMax; // Modulo by columnMax to get the correct column
}

static void DrawCenteredTitle(const uint8_t pnum, const Float width, const Float height)
{
	Float posX, posY;
	menuTexAnim[texIDSkinSelectText].sx = (Sint16)round(width);
	menuTexAnim[texIDSkinSelectText].sy = (Sint16)round(height);
	calculateTitlePosition(pnum, width, height, &posX, &posY);

	NJS_SPRITE _sp;
	_sp.sx = 1.0f;
	_sp.sy = 1.0f;
	_sp.p.x = posX;
	_sp.p.y = posY;
	_sp.tlist = &menuTexlist;
	_sp.tanim = menuTexAnim;
	_sp.ang = 0;

	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	njDrawSprite2D(&_sp, texIDSkinSelectText, -3.0f, 32);
	ResetMaterial();
}

static void DrawBackground(Float posX, Float posY)
{
	NJS_SPRITE _sp;
	_sp.sx = 1.0f;
	_sp.sy = 1.0f;
	_sp.p.x = posX;
	_sp.p.y = posY;
	_sp.tlist = &menuTexlist;
	_sp.tanim = menuTexAnim;
	_sp.ang = 0;

	SetMaterial(0.8f, 0.0f, 0.0f, 0.411f);
	njDrawSprite2D(&_sp, texIDAllBG, -5.0f, NJD_SPRITE_ALPHA | NJD_SPRITE_COLOR);
	ResetMaterial();
}

static void DrawCursor(Float posX, Float posY)
{
	NJS_SPRITE _sp;
	_sp.sx = 1.0f;
	_sp.sy = 1.0f;
	_sp.p.x = posX;
	_sp.p.y = posY;
	_sp.tlist = &menuTexlist;
	_sp.tanim = menuTexAnim;
	_sp.ang = 0;

	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	njDrawSprite2D(&_sp, texIDCursor, -4.0f, 32);
	ResetMaterial();
}

static void DrawLegacyCharIcon(const uint8_t pnum, const uint16_t i, bool alt = false)
{
	NJS_SPRITE _sp;
	_sp.sx = 1.0f;
	_sp.sy = 1.0f;
	_sp.p.x = menu[pnum].itemPos[i].x;
	_sp.p.y = menu[pnum].itemPos[i].y;
	_sp.tlist = &menuTexlist;
	_sp.tanim = menuTexAnim;
	_sp.ang = 0;

	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	uint8_t texID = texIDSonic + menu[pnum].currentCharacter;
	if (alt)
	{
		uint8_t newTexID = getAltTexID(menu[pnum].currentCharacter);
		texID = newTexID > 0 ? newTexID : texID;
	}
	njDrawSprite2D(&_sp, texID, -3.0f, 32);
	ResetMaterial();
}

static void DrawItemsIcon(const uint8_t pnum, const uint8_t i)
{
	NJS_SPRITE _sp;
	_sp.sx = 1.0f;
	_sp.sy = 1.0f;
	_sp.p.x = menu[pnum].itemPos[i].x;
	_sp.p.y = menu[pnum].itemPos[i].y;
	const bool isCustomCover = menu[pnum].items[i].coverTexlist != NULL;
	if (isCustomCover == false)
	{
		_sp.tlist = &menuTexlist;
		_sp.tanim = menuTexAnim;
	}
	else
	{
		_sp.tlist = menu[pnum].items[i].coverTexlist;
		_sp.tanim = &menuCustomIconTexAnim;
	}

	_sp.ang = 0;

	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	njDrawSprite2D(&_sp, isCustomCover ? 0 : texIDUnknownItem, -3.0f, 32);
	ResetMaterial();
}

static void DisplayMenu(const uint8_t pnum)
{
	if (GameState != GameStates_Ingame || menu[pnum].itemCount == 0)
		return;

	njSetTexture(&menuTexlist);

	DrawBackground(menu[pnum].pos.x, menu[pnum].pos.y);
	DrawCenteredTitle(pnum, 150, 22);
	auto index = GetRealMenuItemIndex(pnum);
	DrawCursor(menu[pnum].itemPos[index].x, menu[pnum].itemPos[index].y);
	uint8_t itemOnThePage = 0;
	for (uint8_t i = 0; i < menu[pnum].itemMaxPerPage; i++)
	{
		if (i >= menu[pnum].itemCount)
			break;

		const uint16_t itemIndex = i * (menu[pnum].cursor.curPage + 1);
		if (isLegacy(menu[pnum].items[itemIndex].data.Type))
		{
			DrawLegacyCharIcon(pnum, itemIndex, menu[pnum].items[itemIndex].data.Type == LegacyAlt);
		}
		else
		{
			DrawItemsIcon(pnum, itemIndex);
		}

		itemOnThePage++;
	}

	menu[pnum].itemsOnPage = itemOnThePage;
}

static void MenuDisplay(task* tp)
{
	auto pnum = tp->Data1.twp->id;

	if (menu[pnum].mode != Open)
		return;

	DisplayMenu(pnum);
}


static void MenuController(const uint8_t pnum)
{
	const uint16_t lastSlot = GetMaxIndex(pnum);

	if (MenuButtons_Pressed[pnum] & Buttons_Up)
	{
		if (isCursorOnTop(pnum))
		{
			const int nextIndex = GetNextIndex(pnum, menu[pnum].rowMax - 1, menu[pnum].cursor.curColumn);

			if (nextIndex > lastSlot)
			{
				GoToLastItem(lastSlot, pnum);
			}
			else
			{
				menu[pnum].cursor.curRow = menu[pnum].rowMax - 1;
			}
		}
		else
		{
			menu[pnum].cursor.curRow--;
		}

		PlaySoundProbably(0x8000, 0, 0, 0);
		UpdateCursorPos(pnum);
		menu[pnum].cursor.currentItem = &menu[pnum].items[GetRealMenuItemIndex(pnum)];
	}
	else if (MenuButtons_Pressed[pnum] & Buttons_Down)
	{
		if (isCursorAtTheBottom(pnum))
		{
			menu[pnum].cursor.curRow = 0;
		}
		else
		{
			const int nextIndex = GetNextIndex(pnum, menu[pnum].cursor.curRow + 1, menu[pnum].cursor.curColumn);

			if (nextIndex < lastSlot)
			{
				if (menu[pnum].cursor.curRow < menu[pnum].rowMax - 1)
					menu[pnum].cursor.curRow++;
			}
			else
			{
				GoToLastItem(lastSlot, pnum);
			}
		}

		PlaySoundProbably(0x8000, 0, 0, 0);
		UpdateCursorPos(pnum);
		menu[pnum].cursor.currentItem = &menu[pnum].items[GetRealMenuItemIndex(pnum)];
	}
	else if (MenuButtons_Pressed[pnum] & Buttons_Left)
	{
		if (menu[pnum].cursor.curColumn == 0)
		{
			if (menu[pnum].cursor.curPage > 0)
			{
				menu[pnum].cursor.curPage--;
				return;
			}
			else //if first item on the left side
			{
				const int nextIndex = GetNextIndex(pnum, menu[pnum].cursor.curRow, menu[pnum].columnMax - 1);
				if (nextIndex > lastSlot)
					GoToLastItem(lastSlot, pnum);
				else
					menu[pnum].cursor.curColumn = menu[pnum].columnMax - 1;

			}
		}
		else
		{
			menu[pnum].cursor.curColumn--;
		}

		PlaySoundProbably(0x8000, 0, 0, 0);
		UpdateCursorPos(pnum);
		menu[pnum].cursor.currentItem = &menu[pnum].items[GetRealMenuItemIndex(pnum)];
	}
	else if (MenuButtons_Pressed[pnum] & Buttons_Right)
	{
		if (menu[pnum].cursor.curColumn == menu[pnum].rowMax - 1) //if last item on the right side
		{
			menu[pnum].cursor.curColumn = 0; //swap to new page if it exists and reset index to 0

			if (menu[pnum].cursor.curPage < menu[pnum].pageMax - 1)
				menu[pnum].cursor.curPage++;
		}
		else
		{
			if (menu[pnum].cursor.curColumn< menu[pnum].columnMax- 1 && GetRealMenuItemIndex(pnum) + 1 <= GetMaxIndex(pnum))
				menu[pnum].cursor.curColumn++;
			else
				menu[pnum].cursor.curColumn= 0;
		}

		PlaySoundProbably(0x8000, 0, 0, 0);
		UpdateCursorPos(pnum);
		menu[pnum].cursor.currentItem = &menu[pnum].items[GetRealMenuItemIndex(pnum)];
	}
	else if (MenuButtons_Pressed[pnum] & (Buttons_A | Buttons_Start))
	{
		if (menu[pnum].mode == Open)
		{
			currentSkin[pnum].Type = currentSkin[pnum].Type;
			SwapSkin(pnum);
			menu[pnum].mode = ItemSelected;
		}
		
		PlaySoundProbably(32769, 0, 0, 0);
	}
	else if (MenuButtons_Pressed[pnum] & Buttons_B)
	{
		if (menu[pnum].mode == Open)
			menu[pnum].mode = Exit;
		else if (menu[pnum].mode == ItemSelected)
			menu[pnum].mode = Open;

		PlaySoundProbably(32777, 0, 0, 0);
		menu[pnum].cursor.currentItem = nullptr;
	}
}

static void MenuExec(task* tp)
{
	auto pnum = tp->Data1.twp->id;
	auto twp = tp->Data1.twp;
	auto p = MainCharObj1[pnum];

	if (menu[pnum].itemCount == 0 || !p || p->Action == Action_LightDash)
		return;

	switch (menu[pnum].mode)
	{
	case Closed:
		if (isOpeningMenu(pnum))
		{
			TimerStopped = 1;
			menu[pnum].mode = Init;
		}
		break;
	case Init:
		if (isMenuOpenByAnotherPlayer(pnum))
		{
			menu[pnum].mode = Exit;
		}
		else
		{
			menu[pnum].mode = Open;
			UpdateCursorPos(pnum);
			menu[pnum].cursor.currentItem = &menu[pnum].items[0];
		}
		break;
	case Open:
		MenuController(pnum);
		PrintDebugValues(pnum);
		break;
	case ItemSelected:
		if (++twp->wtimer == 30)
		{
			menu[pnum].mode = Open;
			twp->wtimer = 0;
		}
		break;
	case Exit:
		TimerStopped = 0;
		memset(&menu[pnum].cursor, 0, sizeof(SkinMenuCursor));
		ControllerEnabled[pnum] = 1;
		menu[pnum].mode = Closed;
		break;
	}
}

void BuildItemIconsPos(Float x, Float y, Float widthOffset, Float heightOffset)
{
	Float backupX = x;
	uint16_t count = 0;

	for (uint8_t j = 0; j < PMax; j++)
	{
		for (uint8_t i = 0; i < LengthOfArray(menu[j].itemPos); i++)
		{
			menu[j].itemPos[i].x = menu[j].pos.x + x;
			x += widthOffset;
			count++;

			if (count == menu[j].columnMax)
			{
				x = backupX;
				count = 0;
			}
		}

		count = 0;

		for (uint8_t i = 0; i < LengthOfArray(menu[j].itemPos); i++)
		{
			menu[j].itemPos[i].y = menu[j].pos.y + y;
			count++;

			if (count == menu[j].rowMax)
			{
				y += heightOffset;
				count = 0;
			}
		}
	}
}


void BuildBackgroundMenu(const uint8_t pnum, Float width, Float height)
{
	Float posX, posY;
	menuTexAnim[texIDAllBG].sx = (Sint16)round(width);
	menuTexAnim[texIDAllBG].sy = (Sint16)round(height);
	calculateBackgroundPosition(menuTexAnim[texIDAllBG].sx, menuTexAnim[texIDAllBG].sy, &posX, &posY);
	menu[pnum].pos.x = posX;
	menu[pnum].pos.y = posY;
}


void InitMenuDrawSettings(const uint8_t pnum)
{
	menu[pnum].columnMax = 3;
	menu[pnum].rowMax = 3;
	menu[pnum].itemMaxPerPage = menu[pnum].columnMax * menu[pnum].rowMax;
}


void initMenuItems(const uint8_t pnum)
{
	if (!MainCharacter[pnum] || !MainCharacter[pnum]->Data1.Entity)
		return;

	auto p = MainCharacter[pnum]->Data1.Entity;
	auto pwk = (CharObj2Base*)MainCharacter[pnum]->Data2.Entity;


	menu[pnum].currentCharacter = (Characters)pwk->CharID2;
	menu[pnum].mode = Closed;
	menu[pnum].pageMax = 1;

	currentSkin[pnum].Character = menu[pnum].currentCharacter;

	int count = 0;

	for (uint16_t i = 0; i < skinList.size(); i++)
	{
		if (skinList.at(i).Character == menu[pnum].currentCharacter)
		{
			menu[pnum].items.push_back({ skinList.at(i) });
			menu[pnum].itemCount++;

			if (count == menu[pnum].itemMaxPerPage)
			{
				count = 0;
				menu[pnum].pageMax++;
			}
			else
			{
				count++;
			}

			LoadCoverSkinTex(&menu[pnum].items.back());
		}
	}

}

void ClearMenuData(const uint8_t i)
{
	menu[i].items.clear();
	memset(&menu[i], 0, sizeof(SkinMenuData));
}

void InitMenu()
{
	LoadTextureList("skinMenu", &menuTexlist);

	for (uint8_t j = 0; j < PMax; j++)
	{
		ClearMenuData(j);
		InitMenuDrawSettings(j);
		BuildBackgroundMenu(j, 350.0f, 300.0f); //previously 400-300
		initMenuItems(j);
		BuildItemIconsPos(64.0f, 64.0f, 110.0f, 100.0f); //previously 100-80

		auto p = MainCharObj2[j];
		if (p)
		{
			menuTask[j] = (task*)LoadObject(0, "SkinSelectorTask", (ObjectFuncPtr)MenuExec, LoadObj_Data1 | LoadObj_Data2);
			menuTask[j]->Data1.twp->id = j;
			menuTask[j]->dispDelayed3 = MenuDisplay;
		}
	}
}

void LoadCharacters_r()
{
	LoadCharacters_t.Original();


	for (uint8_t j = 0; j < PMax; j++)
	{
		auto p = MainCharObj2[j];
		if (p)
		{
			for (uint16_t i = 0; i < skinList.size(); i++)
			{
				if (skinList[i].Character == p->CharID2 && isLegacy(skinList[i].Type))
				{
					currentSkin[j] = skinList[i];
					break;
				}
			}
		}
	}

	InitMenu();
}

void __cdecl RunObjectIndex_r(int index)
{
	if (isMenuOpenByAPlayer())
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


void InitMenuHack()
{
	LoadCharacters_t.Hook(LoadCharacters_r);
	RunObjectIndex_t.Hook(RunObjectIndex_r);
}