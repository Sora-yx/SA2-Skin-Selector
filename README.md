<h1 align="center">SA2 Skin Selector Mod</h1>
<p align="center"><img src="https://i.imgur.com/N5k1bpD.jpeg">

</p>

## About

This mod allows you to select a different character skin mod in real time.
This is done in a way so you open a custom menu in game and can select between different skin mods, this also includes the multiplayer costumes from the original game. 

This works by adding an existing skin mod in the ``skins`` folder of the mod, make some specific edit, then the mod will add them in the menu automatically when starting the game. (More information in the section 'how to add skin'.)

## Features
- Can toggle skins in real time including the original alt costumes from the game.
- Option to change the button to open the Menu (Back, LB, RB, Stick press etc...)
- Save System so the selected skins are conserved between sessions and stage changes.
- Support custom models, animations and textures
- Support custom icon for each skin that you want in the menu
- Support custom Hud for each Skin, including life icon and one up
- Support custom effects textures (some mods like Mario, Cosmo and Blaze use it.)

## Limits
- Sounds, Voices and Super Sonic / Shadow model transformation work, but they will only get updated on the next stage
- Full pack mods like DC Characters aren't supported, but combo like Tails mechless and Mech works as well as Sonic and Super Sonic as long as the files use legacy names. (Ie ``sonicmdl`` and ``ssonicmdl``)
- Although Full Packs aren't supported, you can make a separate folder for each character skin from a pack so you can use them anyway.
- ``.PRS`` textures seem to crash the game, it's recommended to convert them to ``.PAK`` using ``Texture Editor`` from [SA Tools](https://mm.reimuhakurei.net/SA%20Tools%20x64.7z).
- If you are in Super Form using the Super Sonic mod, you cannot swap skins until you detransform for technical reasons.


## Installation:

    1) Make sure you have the latest version of SA2 Mod Loader downloaded and installed.
    2) Download the latest version of the mod and place the entire folder in the mods folder.
    3) If all the above steps have been done properly, you should be able to run SAModManager and select the mod in the list.
    4) To configure options, select the mod in the Mod Manager and click on 'Configure Mod' to see all the options.
    5) Click on Save and play! 
	
	
## How to add a skin

### Set up skin information

1) Download (or copy if you already have) any skin mod that you want, then drag drop their whole mod folder in the ``Skins`` folder of Skin Selector.

![TUTO0](https://i.imgur.com/HvIS44y.png)


3) In the skin mod folder that you did copy, rename ``mod.ini`` to ``skin.ini``.

4) Delete all files that aren't needed (``mod.manifest``, ``mod.version``, DLL files...). You obviously want to keep stuff like the ``gd_pc`` and ``ReplaceTex`` folders since those includes the character models, textures (and anims if any).

![tuto1](https://i.imgur.com/VbNhw8i.png)

5) Open ``skin.ini``, add on top ``Character=NameOfTheCharacter``, example: ``Character=Rouge`` if the skin is for Rouge.

![tuto2](https://i.imgur.com/TODMaF5.png)

Here's the list of the keyword supported for all the characters:
```
- Sonic
- Shadow
- Tails
- Miles
- Eggman
- Knuckles
- Rouge
- MechTails
- MechEggman
- Amy
- SuperSonic
- SuperShadow
- MetalSonic
- ChaoWalker
- DarkChaoWalker
- Tikal
- Chaos
```

This is usually enough for a skin mod to work and you can now try it in game.

## Extra notes:
- If the mod requires to disable the jiggle of the character (this is common if a skin mod came with a DLL file) you can add ``DisableJiggle=True`` in ``skin.ini``. 
- This should be rare, but if the skin you want to add has a custom name for the models, animations or textures, you will have to rename them to match SA2's vanilla files. For example the Blaze mod has a file named ``blazemdl.prs``, you will need to rename it ``sonicmdl.prs``, repeat this for animations and textures.
- As mentioned in the limits section earlier, ``.PRS`` textures seem to crash the game, it is recommended to convert them to ``.PAK`` using Texture Editor and the ``Save As`` feature. (This should be rare as most skins tend to use .PAK already.)

## Add an icon to your skin for the menu

If you want to go further, you can add a custom character icon to pick your character so it will look better.

To do it, you will need ``Texture Editor`` from [SA Tools](https://mm.reimuhakurei.net/SA%20Tools%20x64.7z).
Some skins come with a Stage Select Map icon (look for a ``stageMap.pak`` file / folder, or a custom name if the skin mod was using those), then you can extract the character icon using Texture Editor. If the skin didn't have any custom icon, you will have to be creative and make something custom yourself.

Once you have the character icon extracted, you can open Texture Editor and select ``File -> New -> .PAK``

![tuto3](https://i.imgur.com/DR2xaO5.png)

Then click on ``Add...`` and pick your custom icon.
Finally, select ``Edit -> Generate New Gbix`` then click on ``Yes`` on the warning message. This will be useful to avoid textures conflict due to the cache system of the game.

![tuto4](https://i.imgur.com/URHKgQV.png)

Now you can do ``File -> Save As`` and save your pak texture in the PRS folder of your installed skin, name it ``cover`` so the mod can detect it. 

![tuto5](https://i.imgur.com/lpa2Gb4.png)

Nb: ``.PAK`` files are sensitive, so avoid renaming or changing their location, if you really have to do it, use the ``Save As`` feature from Texture Editor.

Nb2: If your skin has multiple models like an Alt version, Super Sonic / Shadow, you can also add a cover for them in the same way, the reserved names are the following ones: ``CoverAlt``, ``CoverSS`` and ``CoverSSH``.

If you have any question you can ask on the [X-Hax Discord](https://discord.gg/gqJCF47) or leave a comment in the GameBanana page of the mod.


## How to Swap Skins in Game

It's very simple:
- During gameplay, press the button to open the menu (default to ``back / share`` on controllers and ``I`` on keyboard)
- The custom menu should shows up and you can select whatever skin you added, if you didn't add anything, this will default to the legacy character and their alt costume (if it exists).
- Press A to swap skin, the menu will blink as a confirmation.
- Press B to close the menu.

That's it!

![end](https://i.imgur.com/JP4JBx6.png)

## Build this repo (for programmers)

1) Install [git for windows](https://gitforwindows.org/)
2) Open CMD and type  ``git clone --recurse-submodules https://github.com/Sora-yx/SA2-Skin-Selector``
3) Get [Visual Studio](https://visualstudio.microsoft.com) (The community version is free)
4) Open the solution and you should be able to build.

If you want to edit the menu, such as its size or the items capacity, you can change its settings in ``menu.cpp`` with the functions ``BuildBackgroundMenu`` and ``BuildItemIconsPos``.

This project uses the ``SDL2`` library to have more buttons to open the menu instead of being limited to the buttons SA2 originally use, it is included in this repo, so you don't have to worry about this.

Enjoy!
