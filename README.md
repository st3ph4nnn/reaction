# Reaction

Reaction is a game to test your reaction time.  
Made using C++17 and RAYLIB 4.0
Raylib: https://www.raylib.com/

# FAQ

1. How can i play the game?

Go to the releases page on the right side of the page.  
If you are using linux, download the linux.zip, otherwise windows.zip  
After that, extract it in a directory and open game.exe or use ./game in terminal for linux  

# FOR DEVELOPERS

## Windows

In order to properly build the game, you will need:

- An IDE of choice
- Latest MinGW x64 DevKit: https://github.com/skeeto/w64devkit (add it to path)
- A terminal

After that, go in to the **build** directory and type in the terminal **mingw32-make.exe OS=WINDOWS**  
Wait a few seconds, and your game should be compiled in the directory 'windows/'

## Linux

In order to properly build the game, you will need:

- An IDE of choice
- A terminal
- Latest G++ (sudo apt install g++)

After that, install these:

### Ubuntu-based

**sudo apt install git libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev**

### Redhat-based

**sudo dnf install git alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel**

After that, you will need to do the following commands in a temporary directory:

- git clone https://github.com/raysan5/raylib.git raylib
- cd raylib/src/
- make PLATFORM=PLATFORM_DESKTOP
- sudo make install

Great. Now you are able to go download the game source, and go in to the build/ folder,  
and type **make OS=LINUX**
