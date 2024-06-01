#include "pch.h"
#include "SDL.h"
#include "input.h"
#include "Windows.h"

//Since sa2 doesn't have Input Mod yet, we will use the SDL2 lib to allow more buttons such as LB / RB and Back.
SDL_GameController* controller = nullptr;
static bool isSDL2 = false;

void SDL2End()
{
    if (controller && isSDL2)
    {
        SDL_GameControllerClose(controller);
        SDL_Quit();
    }
}

bool isOpeningMenu(const uint8_t pnum)
{
    if (isSDL2 && openMenuBtn >= SDL_CONTROLLER_BUTTON_A && openMenuBtn <= SDL_CONTROLLER_BUTTON_MAX)
    {
        return SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)openMenuBtn) || GetKeyState('I') & 0x8000;
    }

    if ((Controllers[pnum].press & openMenuBtn) != 0 || GetKeyState('I') & 0x8000)
        return true;

    return false;
}

void SDL2Runs()
{
    if (!isSDL2 || GameState != GameStates_Ingame)
        return;

    SDL_GameControllerUpdate();
    SDL_Delay(100);
}


void initSDL2(const char* path)
{
    if (openMenuBtn == Buttons_Y)
        return;

    if (!GetModuleHandle(L"SDL2.dll"))
        LoadLibraryA(path);

    if (!GetModuleHandle(L"SDL2.dll") || SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
    {
       PrintDebug("Couldn't load SDL2, this dependency is required to open the Skin Selector menu!\n");
       return;
    }

    for (int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        if (SDL_IsGameController(i))
            controller = SDL_GameControllerOpen(i);

        if (controller)
            break;
    }

    if (!controller)
    {
        PrintDebug("SDl2: No Controller found, keyboard will be used.\n");
        SDL_Quit();
    }

    isSDL2 = true;
}