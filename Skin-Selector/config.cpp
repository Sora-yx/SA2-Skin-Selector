#include "pch.h"
#include "SDL.h"

int openMenuBtn = SDL_CONTROLLER_BUTTON_BACK;
bool saveSkin = true;

void ReadConfig(const char* path) 
{
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

	openMenuBtn = config->getInt("Config", "menuInput", openMenuBtn);	
	saveSkin = config->getBool("Config", "saveSkin", saveSkin);
	delete config;
}