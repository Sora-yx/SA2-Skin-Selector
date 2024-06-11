#pragma once

extern HelperFunctions HelperFunctionsGlobal;
extern std::string modName;
extern std::string modPath;
void ReadConfig(const char* path);

constexpr uint8_t PMax = 4;
constexpr uint8_t CharMax = Characters_Chaos + 1;

const std::string resourcedir = "resource\\gd_pc\\";

#define TaskHook FunctionHook<void, ObjectMaster*>