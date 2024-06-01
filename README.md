<h1 align="center">SA2 Skin Selector Mod</h1>
<p align="center"><img src="https://i.imgur.com/6BlqqB0.png">

</p>

## About

This mod allows you to select a different character skin mod in real time.
This is done in a way so you open a menu in game and can select between different skin mods, this also includes the multiplayer costumes from the original game. 

This works by adding an existing skin mod in the ``skins`` folder of the mod, make some specific edit, then the mod will add them in the menu automatically when starting the game. (More information in the section 'how to add skin'.)

## Features
- Can toggle skins in real time
- Option to change the button to open the Menu (Back, LB, RB, Stick press etc...)
- Support custom models, animations and textures (the name of those files can be custom as well).
- Support custom icon for each skin that you want in the menu
- Support custom Hud for each Skin, including life icon and one up
- Support custom effects textures (some mod like Mario uses it.)


## Installation:

    1) Make sure you have the latest version of SA2 Mod Loader downloaded and installed.
    2) Download the latest version of the mod and place the entire folder in the mods folder.
    3) If all the above steps have been done properly, you should be able to run SAModManager and select the mod in the list.
    4) To configure options, select the mod in the Mod Manager and click on 'Configure Mod' to see all the options.
    5) Click on Save and play! 
	
	
## How to add a skin


1) Download (or copy if you already have) any skin mod that you want, then drag drop their whole mod folder in the ``Skins`` folder of Skin Selector.

![TUTO0](https://i.imgur.com/HvIS44y.png)


3) In the skin mod folder that you did copy, rename ``mod.ini`` to ``skin.ini``.

4) Delete all files that aren't needed (``mod.manifest``, ``mod.version``, DLL files...). You obviously want to keep stuff like the ``gd_pc`` folder which includes the character models, textures (and anims if any).

![tuto1](https://i.imgur.com/VbNhw8i.png)

5) Open ``skin.ini``, add on top ``Character=NameOfTheCharacter``, example: ``Character=Rouge`` if the skin is for Rouge.

![tuto2](https://i.imgur.com/n28s0sH.png)


This is usually enough for a skin mod to work and you can now try it in game.

### Extra notes:
- If the mod requires to disable the jiggle of the character (this is common if a skin mod came with a DLL) you can add ``DisableJiggle=True`` in ``skin.ini``.
- This should be rare, but if the mod has a custom name for the model, animation or textures, you can specify it in ``skin.ini`` like this:

![tuto3](https://i.imgur.com/QqtMwRZ.png)
	

## Build this repo (for programmers)

1) Install [git for windows](https://gitforwindows.org/)
2) Open CMD and type  ``git clone --recurse-submodules https://github.com/Sora-yx/SA2-Skin-Selector``
3) Get [Visual Studio](https://visualstudio.microsoft.com) (The community version is free)
4) Open the solution and you should be able to build.

If you want to edit the menu, such as its size or the items capacity, you can change its settings in ``menu.cpp`` with the functions ``BuildBackgroundMenu`` and ``BuildItemIconsPos``.

This project uses the ``SDL2`` library to have more buttons to open the menu instead of being limited to the buttons SA2 originally use, it is included in this repo, so you don't have to worry about this.

Enjoy!
