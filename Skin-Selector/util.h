#pragma once


std::unique_ptr<ModelInfo> LoadMDL(const char* name, ModelFormat format);
std::unique_ptr<AnimationFile> LoadANM(const char* name);

void toLowercase(std::string& s);
void PrintDebugText(int loc, const char* Format, ...);
void markobjswapped(NJS_OBJECT* obj);
std::string normalizePath(const char* filename);
void FreeTask(ObjectMaster* tp);
void FreeTask_(ObjectMaster* tp);
bool isCharMenuSuper(const uint8_t pnum, const uint8_t charMenu);

bool is_number(const std::string& s);