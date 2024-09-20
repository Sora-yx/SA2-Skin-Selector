#include "pch.h"
#include "SDL.h"
#include "input.h"
#include "Windows.h"

//Since sa2 doesn't have Input Mod yet, we will use the SDL2 lib to allow more buttons such as LB / RB and Back.
SDL_GameController* controller = nullptr;
static bool isSDL2 = false;

void SDL2End()
{
	if (controller && isSDL2)
	{
		SDL_GameControllerClose(controller);
		SDL_Quit();
	}
}

Uint32 getDCInput()
{
	switch (openMenuBtn)
	{
	case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
		return Buttons_C;
	case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
		return Buttons_Z;
	case SDL_CONTROLLER_BUTTON_BACK:
		return Buttons_D;
	}

	return Buttons_Y;
}

bool isOpeningMenu(const uint8_t pnum)
{
	if (ControllerEnabled[pnum] == false)
		return false;

	if (isSDL2 && openMenuBtn >= SDL_CONTROLLER_BUTTON_A && openMenuBtn <= SDL_CONTROLLER_BUTTON_MAX)
	{
		return SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)openMenuBtn) || GetKeyState('I') & 0x8000;
	}


	if ((Controllers[pnum].press & openMenuBtn) != 0 || GetKeyState('I') & 0x8000)
		return true;

	return false;
}

void SDL2Runs()
{
	if (GameState != GameStates_Ingame)
		return;


	SDL_GameControllerUpdate();
	SDL_Delay(100);
}


void initSDL2(const char* path)
{
	if (openMenuBtn == Buttons_Y)
		return;

	auto helper = HelperFunctionsGlobal;
	auto InputControls = HelperFunctionsGlobal.Mods->find("sa2-input-controls");
	auto skinSelector = HelperFunctionsGlobal.Mods->find("sa2.skin.selector");
	HMODULE CharSelPlus = GetModuleHandle(L"CharacterSelectPlus.dll");
	HMODULE CharSel = GetModuleHandle(L"SA2CharSel.dll");

	if (InputControls && skinSelector)
	{
		int indexInput = -1;
		int indexSkin = -1;
		int charPlusSkin = -1;

		for (uint16_t i = 0; i < helper.Mods->size(); i++)
		{
			if (helper.Mods->at(i).ID == InputControls->ID)
				indexInput = i;

			if (helper.Mods->at(i).ID == skinSelector->ID)
				indexSkin = i;

			if (CharSelPlus)
			{
				if (helper.Mods->at(i).DLLHandle == CharSelPlus)
					charPlusSkin = i;
			}
			else if (CharSel)
			{
				if (helper.Mods->at(i).DLLHandle == CharSel)
					charPlusSkin = i;
			}
		}

		if (indexSkin != -1)
		{
			if (indexInput != -1)
			{
				if (indexInput > indexSkin)
				{
					MessageBox(MainWindowHandle, L"Error, Skin Selector mod is loaded before Input Controls, please exit the game and load Skin Selector after Input Controls for the best compatibility.", L"Skin Selector - Mod Order Error", MB_ICONWARNING);
				}
			}

			if (charPlusSkin != -1)
			{
				if (charPlusSkin > indexSkin)
				{
					MessageBox(MainWindowHandle, L"Error, Skin Selector mod is loaded before Character Select mod, please exit the game and load Skin Selector after Character Select for the best compatibility.", L"Skin Selector - Mod Order Error", MB_ICONWARNING);
				}
			}
		}


	}


	if (!GetModuleHandle(L"SDL2.dll"))
		LoadLibraryA(path);

	if (!GetModuleHandle(L"SDL2.dll"))
	{
		PrintDebug("Couldn't load SDL2, this dependency is required to open the Skin Selector menu!\n");
		return;
	}

	if (SDL_Init(SDL_INIT_GAMECONTROLLER) >= 0)
	{

		for (int i = 0; i < SDL_NumJoysticks(); ++i)
		{
			if (SDL_IsGameController(i))
				controller = SDL_GameControllerOpen(i);

			if (controller)
				break;
		}

		if (!controller)
		{
			PrintDebug("SDl2: No Controller found, keyboard will be used.\n");
			SDL_Quit();
		}

		isSDL2 = true;
	}

}