#include "pch.h"
#include "SDL.h"

bool playMusic = true;
int openMenuBtn = SDL_CONTROLLER_BUTTON_BACK;

void ReadConfig(const char* path) 
{
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

	openMenuBtn = config->getInt("Config", "menuInput", openMenuBtn);
	delete config;
}