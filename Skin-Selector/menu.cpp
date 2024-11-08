#include "pch.h"
#include "menu.h"
#include <iostream>
#include <filesystem>
#include "FileSystem.h"
#include "input.h"
#include "patches.h"
#include "save.h"
#include "Jiggle.h"

FunctionHook<void> LoadCharacters_t((intptr_t)LoadCharacters);
FunctionHook<void> FinalHazard_Init_t((intptr_t)FinalHazard_Init);

static NJS_TEXNAME menuTex[27];
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
	Reset,
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
	texIDEggmanMAlt,
	texIDSuperSonic,
	texIDSuperShadow,
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

const Sint16 cursorSize = 82;
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
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDSuperSonic, 0x0 },
	{ charIconX, charIconY, charIconX / 2, charIconY / 2, 8, 8, 0x0F4, 0x0F4, texIDSuperShadow, 0x0 },
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

bool isMenuOpen(uint8_t playerID)
{

	if (MainCharObj2[playerID] && menu[playerID].mode != Closed)
		return true;

	return false;
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

bool isMenuOpenByAPlayer()
{
	for (uint8_t j = 0; j < PMax; j++)
	{
		if (menu[j].mode != Closed)
			return true;
	}

	return false;
}

bool isMenuFullyOpenByAPlayer()
{
	for (uint8_t j = 0; j < PMax; j++)
	{
		if (menu[j].mode >= Open && menu[j].mode != Closed)
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

static void DrawCursor(Float posX, Float posY, const Float scl)
{
	NJS_SPRITE _sp;
	_sp.sx = scl;
	_sp.sy = scl;
	_sp.p.x = posX;
	_sp.p.y = posY;
	_sp.tlist = &menuTexlist;
	_sp.tanim = menuTexAnim;
	_sp.ang = 0;

	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	njDrawSprite2D(&_sp, texIDCursor, -4.0f, 32);
	ResetMaterial();
}

static void DrawLegacyCharIcon(const uint8_t pnum, const uint8_t i, Characters curChar, Float scl, bool alt = false)
{
	NJS_SPRITE _sp;
	_sp.sx = scl;
	_sp.sy = scl;
	_sp.p.x = menu[pnum].itemPos[i].x;
	_sp.p.y = menu[pnum].itemPos[i].y;
	_sp.tlist = &menuTexlist;
	_sp.tanim = menuTexAnim;
	_sp.ang = 0;

	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
	uint8_t texID = texIDSonic + menu[pnum].currentCharacter;
	if (menu[pnum].currentCharacter > Characters_Amy) //handle super sonic and Big offset in the charList
		texID -= 3;


	if (alt)
	{
		uint8_t newTexID = getAltTexID(menu[pnum].currentCharacter);
		texID = newTexID > 0 ? newTexID : texID;
	}
	else if (curChar == Characters_SuperSonic)
	{
		texID = texIDSuperSonic;
	}
	else if (curChar == Characters_SuperShadow)
	{
		texID = texIDSuperShadow;
	}

	njDrawSprite2D(&_sp, texID, -3.0f, 32);
	ResetMaterial();
}

static void DrawItemsIcon(const uint8_t pnum, const uint8_t i, const uint16_t itemIndex, Float scl)
{
	NJS_SPRITE _sp;
	_sp.sx = scl;
	_sp.sy = scl;
	_sp.p.x = menu[pnum].itemPos[itemIndex].x;
	_sp.p.y = menu[pnum].itemPos[itemIndex].y;
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
	auto p = MainCharObj1[pnum];
	auto pwp = MainCharObj2[pnum];

	if (GameState != GameStates_Ingame)
		return;

	if (menu[pnum].itemCount == 0 || !p || p->Action == Action_LightDash || !pwp || pwp->Powerups & Powerups_Dead)
		return;

	Float Scl = njCos(((unsigned int)(5 * FrameCountIngame) * 182.0f)) * 0.1f + 1.1f;
	njSetTexture(&menuTexlist);
	DrawBackground(menu[pnum].pos.x, menu[pnum].pos.y);
	DrawCenteredTitle(pnum, 150, 22);
	auto index = GetRealMenuItemIndex(pnum);
	DrawCursor(menu[pnum].itemPos[index - (menu[pnum].itemMaxPerPage * menu[pnum].cursor.curPage)].x, menu[pnum].itemPos[index - (menu[pnum].itemMaxPerPage * menu[pnum].cursor.curPage)].y, Scl);
	uint8_t itemCountOnPage = 0;

	for (uint8_t i = 0 + menu[pnum].itemMaxPerPage * menu[pnum].cursor.curPage; i < menu[pnum].itemCount; i++)
	{
		const uint16_t itemIndexPos = i - (menu[pnum].itemMaxPerPage * menu[pnum].cursor.curPage);

		if (itemIndexPos >= menu[pnum].itemMaxPerPage)
			break;

		Scl = index == i ? njCos(((unsigned int)(5 * FrameCountIngame) * 182.0f)) * 0.1f + 1.1f : 1.0f;
		if (isLegacy(menu[pnum].items[i].data.Type))
		{
			DrawLegacyCharIcon(pnum, itemIndexPos, (Characters)pwp->CharID2, Scl, menu[pnum].items[itemIndexPos].data.Type == LegacyAlt);
		}
		else
		{
			DrawItemsIcon(pnum, i, itemIndexPos, Scl);
		}

		itemCountOnPage++;
	}

	menu[pnum].itemsOnPage = itemCountOnPage;
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
	const uint16_t lastSlot = menu[pnum].itemsOnPage - 1;
	auto curChar = menu[pnum].currentCharacter;

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
				if (menu[pnum].cursor.curRow < menu[pnum].rowMax - 1 && GetRealMenuItemIndex(pnum) + 1 <= GetMaxIndex(pnum))
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
				if (menu[pnum].cursor.curRow < menu[pnum].rowMax - 1 && GetRealMenuItemIndex(pnum) + 1 <= GetMaxIndex(pnum))
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
				menu[pnum].cursor.curColumn = 0;
				menu[pnum].cursor.curRow = 0;
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
			{
				menu[pnum].cursor.curPage++;
				menu[pnum].cursor.curColumn = 0;
				menu[pnum].cursor.curRow = 0;
			}
		}
		else
		{
			if (menu[pnum].cursor.curColumn < menu[pnum].columnMax - 1 && GetRealMenuItemIndex(pnum) + 1 <= GetMaxIndex(pnum))
				menu[pnum].cursor.curColumn++;
			else
				menu[pnum].cursor.curColumn = 0;
		}

		PlaySoundProbably(0x8000, 0, 0, 0);
		UpdateCursorPos(pnum);
		menu[pnum].cursor.currentItem = &menu[pnum].items[GetRealMenuItemIndex(pnum)];
	}
	else if (MenuButtons_Pressed[pnum] & (Buttons_A | Buttons_Start))
	{
		if (menu[pnum].mode == Open)
		{
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


extern bool deleteTime;
extern bool isCallbackRunning;
void BuildMenu(const uint8_t pnum);
void ClearMenuData(const uint8_t i);
static void MenuExec(task* tp)
{
	auto pnum = tp->Data1.twp->id;
	auto twp = tp->Data1.twp;
	auto p = MainCharObj1[pnum];
	auto pwp = MainCharObj2[pnum];


	if (GameState != GameStates_Ingame || menu[pnum].itemCount == 0 || !p || p->Action == Action_LightDash || !pwp)
		return;

	if (pwp->Powerups & Powerups_Dead)
	{
		if (menu[pnum].mode != Closed)
			menu[pnum].mode = Exit;
	}



	const auto charID2 = pwp->CharID2;
	const auto menuChar = menu[pnum].currentCharacter;

	switch (menu[pnum].mode)
	{
	case Closed:
		if (isOpeningMenu(pnum) && !isCallbackRunning && !isSuper(pwp))
		{
			TimerStopped = 1;
			PauseDisabled = 1;
			deleteEyeTracker[pnum] = true;

			if (charID2 != menuChar)
				menu[pnum].mode = Reset;
			else
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
			if (CurrentLevel != LevelIDs_FinalHazard)
				ControllerEnabled[pnum] = false;
			menu[pnum].mode = Open;
			UpdateCursorPos(pnum);
			menu[pnum].cursor.currentItem = &menu[pnum].items[0];
			twp->wtimer = 0;
		}
		break;
	case Open:

		MenuController(pnum);

		if (menu[pnum].cursor.currentItem && menu[pnum].cursor.currentItem->text != "")
			DrawSubtitlesSA2(1.0f, menu[pnum].cursor.currentItem->text.c_str(), -1, TextLanguage, 0, 0);
		break;
	case ItemSelected:
		if (++twp->wtimer == 15)
		{
			menu[pnum].mode = Open;
			twp->wtimer = 0;
		}
		break;
	case Exit:
		ControllerEnabled[pnum] = true;
		if ((pwp->Powerups & Powerups_Dead) == 0)
			InitEyesTrack(MainCharObj2[pnum]->CharID2, pnum);
		if (pwp->AnimInfo.Current != 54)
		{
			TimerStopped = 0;
			PauseDisabled = 0;
		}
		memset(&menu[pnum].cursor, 0, sizeof(SkinMenuCursor));
		menu[pnum].mode = Closed;
		if (DrawSubtitlesPtr)
			FreeTask(DrawSubtitlesPtr);
		break;
	case Reset:
		BuildMenu(pnum);
		menu[pnum].mode = Init;
		break;
	}
}

void BuildItemIconsPos(const uint8_t pnum, Float x, Float y, Float widthOffset, Float heightOffset)
{
	Float backupX = x;
	uint16_t count = 0;


	for (uint8_t i = 0; i < LengthOfArray(menu[pnum].itemPos); i++)
	{
		menu[pnum].itemPos[i].x = menu[pnum].pos.x + x;
		x += widthOffset;
		count++;

		if (count == menu[pnum].columnMax)
		{
			x = backupX;
			count = 0;
		}
	}

	count = 0;

	for (uint8_t i = 0; i < LengthOfArray(menu[pnum].itemPos); i++)
	{
		menu[pnum].itemPos[i].y = menu[pnum].pos.y + y;
		count++;

		if (count == menu[pnum].rowMax)
		{
			y += heightOffset;
			count = 0;
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

void FreeMenuTexlistCover()
{
	for (uint8_t pnum = 0; pnum < PMax; pnum++)
	{
		for (uint8_t i = 0; i < menu[pnum].itemCount; i++)
		{
			if (isLegacy(menu[pnum].items[i].data.Type) == false && menu[pnum].items[i].coverTexlist != nullptr)
			{
				FreeTexList(menu[pnum].items[i].coverTexlist);
				std::string id = std::to_string(menu[pnum].items[i].data.uniqueID);
				std::string fileName = menu[pnum].items[i].data.Cover + id;
				const std::string legacyTexPath = resourcedir + fileName + ".prs";
				HelperFunctionsGlobal.UnreplaceFile(legacyTexPath.c_str());
			}
		}
	}
}


void initMenuItems(const uint8_t pnum)
{
	if (!MainCharacter[pnum] || !MainCharacter[pnum]->Data1.Entity)
		return;

	auto p = MainCharacter[pnum]->Data1.Entity;
	auto pwk = (CharObj2Base*)MainCharacter[pnum]->Data2.Entity;
	auto curChar = (Characters)pwk->CharID2;

	menu[pnum].mode = Closed;
	menu[pnum].pageMax = 1;

	currentSkin[pnum][pwk->CharID2].Character = curChar;
	menu[pnum].currentCharacter = curChar;

	uint16_t count = 0;
	uint16_t index = 0;
	std::vector<SkinMenuItem> vec;

	for (uint16_t i = 0; i < skinList.size(); i++)
	{
		if (skinList.at(i).Character == menu[pnum].currentCharacter)
		{
			std::string text = "\a" + skinList.at(i).Name + " - " + skinList.at(i).Author;
			vec.push_back({ skinList.at(i), {0}, false, nullptr, text });

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

			LoadCoverSkinTex(&vec[index]);
			index++;
		}
	}

	if (vec.size() > 0)
	{
		SkinMenuItem* skin_arr = new SkinMenuItem[vec.size()];
		for (uint16_t i = 0; i < vec.size(); i++)
			skin_arr[i] = vec.at(i);

		menu[pnum].items = skin_arr;
	}
}

void ClearMenuData(const uint8_t i)
{
	if (menu[i].itemCount > 0 && menu[i].items)
	{
		delete[] menu[i].items;
		menu[i].items = nullptr;
		menu[i].itemCount = 0;
	}
	memset(&menu[i], 0, sizeof(SkinMenuData));
}

FunctionHook<void> DeleteLand_t(0x439C80);
void DeleteLand_r()
{
	FreeTexList(&menuTexlist);
	FreeMenuTexlistCover();
	DeleteLand_t.Original();
}

void BuildMenu(const uint8_t pnum)
{
	ClearMenuData(pnum);
	InitMenuDrawSettings(pnum);
	BuildBackgroundMenu(pnum, 350.0f, 310.0f); //previously 400-300
	initMenuItems(pnum);
	BuildItemIconsPos(pnum, 64.0f, 64.0f, 110.0f, 90.0f); //previously 100-80
}

void InitMenu()
{
	LoadTextureList("skinMenu", &menuTexlist);

	for (uint8_t j = 0; j < PMax; j++)
	{
		auto p = MainCharObj2[j];

		if (p)
		{
			BuildMenu(j);
			menuTask[j] = (task*)LoadObject(0, "SkinSelectorTask", (ObjectFuncPtr)MenuExec, LoadObj_Data1 | LoadObj_Data2);
			menuTask[j]->Data1.twp->id = j;
			menuTask[j]->dispDelayed3 = MenuDisplay;
		}
	}
}

void FinalHazard_Init_r()
{
	FinalHazard_Init_t.Original();
	InitMenu();
}

void LoadCharacters_r()
{
	LoadCharacters_t.Original();

	for (uint8_t i = 0; i < PMax; i++)
	{
		for (uint8_t j = 0; j < CharMax; j++)
		{
			if (currentSkin[i][j].Name == "") //if current skin empty
			{
				for (uint8_t k = 0; k < skinList.size(); k++)
				{
					if (skinList[k].Character == j)
					{
						currentSkin[i][j] = skinList.at(k);
						break;
					}
				}
			}

			if (MainCharObj2[i] && MainCharObj2[i]->CharID2 == j)
				CheckAndLoadJiggle(i, j);
		}
	}

	if (CurrentLevel != LevelIDs_FinalHazard)
		InitMenu();
}


void InitMenuHack()
{
	LoadCharacters_t.Hook(LoadCharacters_r);
	FinalHazard_Init_t.Hook(FinalHazard_Init_r);
	DeleteLand_t.Hook(DeleteLand_r);
}