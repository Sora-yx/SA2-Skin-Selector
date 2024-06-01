#include "pch.h"
#include <iostream>
#include <algorithm>


const char* ModelFormatStrings[]{
	"collision",
	"chunk",
	"battle"
};

std::unique_ptr<ModelInfo> LoadMDL(const char* name, ModelFormat format)
{
	std::string fullPath;

	if (format == ModelFormat_Chunk) 
	{
		fullPath = "resource\\gd_PC\\Models\\";
	}

	fullPath += name;

	switch (format) {
	case ModelFormat_Basic:
		fullPath += ".sa1mdl";
		break;
	case ModelFormat_Chunk:
		fullPath += ".sa2mdl";
		break;
	case ModelFormat_SA2B:
		fullPath += ".sa2bmdl";
		break;
	}

	const char* foo = fullPath.c_str();

	std::unique_ptr<ModelInfo> temp = std::make_unique<ModelInfo>(HelperFunctionsGlobal.GetReplaceablePath(foo));
	std::string success = modName + "Loaded %s model: %s.";
	std::string failed = modName + "Failed loading %s model: %s.";

	if (temp->getformat() == format) 
	{
		PrintDebug(success.c_str(), ModelFormatStrings[(int)format - 1], name);
	}
	else {
		PrintDebug(failed.c_str(), ModelFormatStrings[(int)format - 1], name);
	}

	return temp;
}

std::unique_ptr<AnimationFile> LoadANM(const char* name)
{
	std::string fullPath = "resource\\gd_PC\\animations\\";
	fullPath = fullPath + name + ".saanim";

	std::unique_ptr<AnimationFile> temp = std::make_unique<AnimationFile>(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (temp->getmodelcount())
	{
		PrintDebug("Loaded anim %s\n", name);
		return temp;
	}
	else
	{
		PrintDebug("Failed to load anim %s\n", name);
		return nullptr;
	}
}

void toLowercase(std::string& s) 
{
	std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
}

std::string GetExtension(const std::string& path)
{
	auto dot = path.rfind('.');
	if (dot == std::string::npos)
	{
		return std::string();
	}

	return path.substr(dot);
}

void PrintDebugText(int loc, const char* Format, ...)
{
	return HelperFunctionsGlobal.DisplayDebugStringFormatted(loc, Format);
}

void markobjswapped(NJS_OBJECT* obj)
{
	while (obj)
	{
		IsByteswapped(&obj->evalflags);
		IsByteswapped(&obj->model);
		IsByteswapped(&obj->pos[0]);
		IsByteswapped(&obj->pos[1]);
		IsByteswapped(&obj->pos[2]);
		IsByteswapped(&obj->ang[0]);
		IsByteswapped(&obj->ang[1]);
		IsByteswapped(&obj->ang[2]);
		IsByteswapped(&obj->scl[0]);
		IsByteswapped(&obj->scl[1]);
		IsByteswapped(&obj->scl[2]);
		IsByteswapped(&obj->child);
		IsByteswapped(&obj->sibling);
		if (obj->chunkmodel)
		{
			IsByteswapped(&obj->chunkmodel->vlist);
			IsByteswapped(&obj->chunkmodel->plist);
			IsByteswapped(&obj->chunkmodel->center.x);
			IsByteswapped(&obj->chunkmodel->center.y);
			IsByteswapped(&obj->chunkmodel->center.z);
			IsByteswapped(&obj->chunkmodel->r);
		}
		if (obj->child)
			markobjswapped(obj->child);
		obj = obj->sibling;
	}
}

inline int backslashes(int c)
{
	return c == '/' ? '\\' : c;
}

std::string normalizePath(const char* filename)
{
	std::string path = filename;
	std::transform(path.begin(), path.end(), path.begin(), backslashes);
	if (path.length() > 2 && (path[0] == '.' && path[1] == '\\'))
		path = path.substr(2, path.length() - 2);
	std::transform(path.begin(), path.end(), path.begin(), ::tolower);
	return path;
}