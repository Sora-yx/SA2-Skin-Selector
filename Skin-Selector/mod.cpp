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


extern "C" {

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		HelperFunctionsGlobal = helperFunctions;
		std::filesystem::path pathObj(path);
		modName = pathObj.filename().string();
		modPath = path;

		hdGUI = GetModuleHandle(L"HD GUI.dll") != NULL;

		ReadConfig(path); //get mod settings by the user
	
		initSkinList(path);
		InitMenuHack();
		InitPatches();
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