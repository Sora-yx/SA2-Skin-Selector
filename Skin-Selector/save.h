#pragma once

#include <string.h>
#include "Skin.h"

struct SkinSave
{
	const char* Name;
	const char* FolderPath;

};

void Save(const uint8_t pnum, const uint8_t charID2);
bool Load(const uint8_t pnum, const uint8_t charID2);
void initSave();