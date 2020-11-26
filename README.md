# Dragonfly
This 2D C++ engine uses ASCII art for it's graphics. This engine was made over the span of three weeks for my IMGD3000 class at Worcester Polytechnic Institute. This engine is fully featured and ready to be used to create games. It's a pretty basic engine, but it can be extended to use SFML's full capabilities.

## FEATURES
- Graceful engine and window start up and shut down.
- Resource handling
  - Parse loaded sprite files into ASCII animations.
  - Load audio from file.
- Audio (SFML sounds and music)
- Event dispatching.
  - Mouse and keyboard input.
  - View and world out of bounds.
- Objects
  - Render ASCII characters anywhere in the world.
  - Collision (Dispatches collide event to both objects).
  - Can exist and update outside of the viewable area, but do not update when outside of a larger area representing the game world.
  - Can be rendered as anything SFML supports by overriding it's draw function.
- Transparency
- Layering
- Runtime logging.

## PLATFORM
Made for Windows 10 x64
Mac and Linux should work fine as long as you update the time functions in utility.cpp, but be aware that I haven't tested it.

## HOW TO BUILD
Download SFML (>= 2.5) here https://www.sfml-dev.org/download.php
Copy the SFML folder into the parent folder of the root folder of this project, so that this project and SFML are siblings
Rename SFML folder to SFML-2.5
Launch dragonfly.sln with Visual Studio
Build
Run

### NOTE
'sounds', 'sprites', 'game.cpp', 'TestObject.h', and 'TestObject.cpp' are not required and are only used for testing. Feel free to remove them if you plan on using this.
