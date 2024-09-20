#include "pch.h"
#include <iostream>
#include <filesystem>
#include <string>
#include "menu.h"
#include "input.h"
#include "patches.h"
#include <direct.h>	
#include "save.h"
#include "Jiggle.h"

HelperFunctions HelperFunctionsGlobal;
std::string modName = "Skin Selector";
std::string modPath = "";
bool hdGUI = false;

static std::string build_mod_path(const char* modpath, const char* path)
{
	std::stringstream result;
	char workingdir[FILENAME_MAX]{};

	result << _getcwd(workingdir, FILENAME_MAX) << "\\" << modpath << "\\" << path;

	return result.str();
}

void CheckModsOrder(const HelperFunctions& helper)
{
	auto InputControls = helper.Mods->find("sa2-input-controls");
	auto skinSelector = helper.Mods->find("sa2.skin.selector");
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

}

extern "C" {


	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		HelperFunctionsGlobal = helperFunctions;

		if (helperFunctions.Version < 12)
		{
			MessageBox(MainWindowHandle, L"Your Mod Loader does not support the API Version 12, please Update your Mod Loader for this mod to work.", L"Skin Selector Mod - Error Mod Loader Out of Date", MB_ICONWARNING);
			return;
		}

		std::filesystem::path pathObj(path);
		modName = pathObj.filename().string();
		modPath = path;


		ReadConfig(path); //get mod settings by the user
	
		initSkinList(path);
		InitMenuHack();
		InitPatches();
		CheckModsOrder(helperFunctions);
		std::string s = build_mod_path(path, "SDL2.dll");
		initSDL2(s.c_str());
		InitJiggleHacks();
		initSave();

	}

	__declspec(dllexport) void __cdecl OnFrame()
	{
		
	}


	__declspec(dllexport) void __cdecl OnExit()
	{
		SDL2End();
		for (uint8_t j = 0; j < PMax; j++)
		{
			ClearMenuData(j);
		}
	}


	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}