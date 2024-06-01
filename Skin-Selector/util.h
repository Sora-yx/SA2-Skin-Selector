#pragma once


std::unique_ptr<ModelInfo> LoadMDL(const char* name, ModelFormat format);
std::unique_ptr<AnimationFile> LoadANM(const char* name);

void toLowercase(std::string& s);
std::string GetExtension(const std::string& path);
void PrintDebugText(int loc, const char* Format, ...);
void markobjswapped(NJS_OBJECT* obj);
std::string normalizePath(const char* filename);