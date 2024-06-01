#include "pch.h"
#include "FileSystem.h"
#include <stdio.h>
#include <string.h>
#include <Shlwapi.h>

VoidFunc(sub_4297F0, 0x4297F0);
StdcallFunctionPointer(void, sub_419FC0, (void*), 0x419FC0);
FunctionPointer(void, sub_7A5974, (void*), 0x7A5974);
DataPointer(int, dword_1A55800, 0x1A55800);
DataPointer(int, dword_1AF191C, 0x1AF191C);
DataPointer(void*, dword_1AF1918, 0x1AF1918);
FunctionPointer(void, sub_48FA80, (NJS_OBJECT*, void*), 0x48FA80);

const std::string resourcedir = "resource\\gd_pc\\";
#pragma warning(disable : 4996)
#pragma comment(lib, "Shlwapi.lib")
std::unordered_map<ModelIndex*, std::list<ModelInfo>> modelfiles;


//Custom function inspired from the hack the Mod Loader originally does. This is used to load skin models in the subfolders of the mod.
ModelIndex* __cdecl LoadSkinMdlFile(const char* filename, const char* path)
{
	ModelIndex* result = nullptr;
	char dir[MAX_PATH];
	PathCombineA(dir, resourcedir.c_str(), filename);
	PathRemoveExtensionA(dir);
	char* fn = PathFindFileNameA(dir);
	char combinedpath[MAX_PATH];
	PathCombineA(combinedpath, dir, fn);
	PathAddExtensionA(combinedpath, ".ini");
	std::string newResourceDir = path + (std::string)"\\gd_PC\\" + fn + "\\" + fn + ".ini";
	const char* repfn = newResourceDir.c_str();

	if (PathFileExistsA(repfn))
	{
		FILE* f_mod_ini = fopen(repfn, "r");
		std::unique_ptr<IniFile> ini(new IniFile(f_mod_ini));
		fclose(f_mod_ini);
		const IniGroup* indexes = ini->getGroup("");
		strncpy_s(dir, repfn, MAX_PATH);
		PathRemoveFileSpecA(dir);
		WIN32_FIND_DATAA data;
		HANDLE hfind = FindFirstFileA((std::string(dir) + "\\*.sa2mdl").c_str(), &data);

		if (hfind == INVALID_HANDLE_VALUE)
			return result;

		std::list<ModelInfo> files;
		std::vector<ModelIndex> modelindexes;
		sub_4297F0();
		do
		{
			PathCombineA(combinedpath, dir, data.cFileName);
			ModelInfo modelfile(combinedpath);
			files.push_back(modelfile);
			markobjswapped(modelfile.getmodel());
			for (auto i = indexes->cbegin(); i != indexes->cend(); i++)
			{
				void* found = modelfile.getdata(i->second);
				if (found != nullptr)
				{
					int ind = stoi(i->first);
					ModelIndex index = { ind, (NJS_OBJECT*)found };
					if (ind >= 0 && ind < 532 && !CharacterModels[ind].Model)
						CharacterModels[ind] = index;
					modelindexes.push_back(index);
				}
			}
		} while (FindNextFileA(hfind, &data) != 0);
		FindClose(hfind);
		ModelIndex endmarker = { -1, (NJS_OBJECT*)-1 };
		modelindexes.push_back(endmarker);
		result = new ModelIndex[modelindexes.size()];
		memcpy(result, modelindexes.data(), sizeof(ModelIndex) * modelindexes.size());
		modelfiles[result] = files;

		//idk wtf they do here
		--dword_1A55800;
		if (dword_1AF191C)
		{
			auto v13 = dword_1AF1918;
			auto v14 = *((DWORD*)dword_1AF1918 + 1);
			auto v15 = *((DWORD*)dword_1AF1918 + 1);
			if (!*(BYTE*)(v14 + 21))
			{
				do
				{
					sub_419FC0(*(void**)(v15 + 8));
					v15 = *(DWORD*)v15;
					sub_7A5974((void*)v14);
					v14 = v15;
				} while (!*(BYTE*)(v15 + 21));
				v13 = dword_1AF1918;
			}
			*((DWORD*)v13 + 1) = (DWORD)v13;
			dword_1AF191C = 0;
			*(DWORD*)dword_1AF1918 = (DWORD)dword_1AF1918;
			*((DWORD*)dword_1AF1918 + 2) = (DWORD)dword_1AF1918;
		}
	}

	return result;
}

void __cdecl ReleaseSkinMDLFile(ModelIndex* a1)
{
	if (a1->Index != -1)
	{
		ModelIndex* v1 = a1;
		do
		{
			if (v1->Index >= 0 && v1->Index < 532 && CharacterModels[v1->Index].Model == v1->Model)
				CharacterModels[v1->Index].Model = 0;
			++v1;
		} while (v1->Index != -1);
	}
	if (modelfiles.find(a1) != modelfiles.cend())
	{
		modelfiles.erase(a1);
		delete[] a1;
	}
	else
	{
		*((DWORD*)a1 - 1) = 0x89ABCDEFu;
		MemoryManager->Deallocate((AllocatedMem*)a1 - 4, (char*)"..\\..\\src\\file_ctl.c", 1091);
	}
}
