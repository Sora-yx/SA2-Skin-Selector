#pragma once

#pragma pack(push, 1)
#include <string.h>
#include "Skin.h"

struct SkinSave
{
	const char* Name;
	const char* FolderPath;
	const char* SuperFormPath;
	const char* MechPath;
	bool AltCostume;
	bool Legacy;

};

void Save(const uint8_t pnum, const uint8_t charID2);
void Load(const uint8_t pnum, const uint8_t charID2);
void initSave();

#pragma pack(pop)