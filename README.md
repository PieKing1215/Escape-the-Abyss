# Escape the Dungeon
This 2D C++ game uses [Dragonfly](https://github.com/dman926/dragonfly). The game consists of the player fighting their way out of a deep abyss, with randomly generated levels with hidden loading loading allowing for a virtually endless game.

## PLATFORM
Made for Windows 10 x64. Mac and Linux should work fine as long as you update the time functions in utility.cpp, but be aware that I haven't tested it.

## HOW TO BUILD
1. Download SFML (>= 2.5) here https://www.sfml-dev.org/download.php
2. Copy the SFML folder into the parent folder of the root folder of this project, so that this project and SFML are siblings
3. Rename SFML folder to SFML-2.5
4. Launch dragonfly.sln with Visual Studio
5. Build
6. Run (May need to manually copy OpenAL.dll from SFML to executable location)