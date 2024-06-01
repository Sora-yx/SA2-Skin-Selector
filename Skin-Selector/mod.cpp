#include "pch.h"
#include <iostream>
#include <filesystem>
#include <string>
#include "menu.h"
#include "input.h"
#include <direct.h>	

HelperFunctions HelperFunctionsGlobal;
std::string modName = "Skin Selector";

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

		ReadConfig(path); //get mod settings by the user
	
		initSkinList(path);
		InitMenuHack();
		std::string s = build_mod_path(path, "SDL2.dll");
		initSDL2(s.c_str());
		//WriteData<1>((int*)0x77F6B0, 0xC3);
		//WriteData<5>((int*)0x43F7F4, 0x90);
	}

	__declspec(dllexport) void __cdecl OnFrame()
	{

	}


	__declspec(dllexport) void __cdecl OnExit()
	{
		SDL2End();
	}


	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}