[![EN](https://user-images.githubusercontent.com/9499881/33184537-7be87e86-d096-11e7-89bb-f3286f752bc6.png)](https://github.com/r57zone/RE4ExtendedControl/) 
[![RU](https://user-images.githubusercontent.com/9499881/27683795-5b0fbac6-5cd8-11e7-929c-057833e01fb1.png)](https://github.com/r57zone/RE4ExtendedControl/blob/master/README.RU.md)
← Choose language | Выберите язык

# Resident Evil 4 Extended Control
Resident Evil 4 (2014) extended control for Xbox gamepads. The mod adds support for quick weapon switching, changes the run, inventory, and Ashley command buttons, and adds aiming to the right stick.

# Control
[![](https://github-production-user-asset-6210df.s3.amazonaws.com/9499881/275010772-cfe5f18c-53bd-492c-b6f0-60f68fbc2d7f.png)](https://youtu.be/yFFzgANoAXo)

The inventory is moved to the `Y` button and the map to the `Start` button. The start button is used to move items in the inventory.


The run button is duplicated on the `RB` button.

[![](https://github-production-user-asset-6210df.s3.amazonaws.com/9499881/275028951-b59e1f5e-dcd0-4322-bc51-58b5ff594a73.jpg)](https://youtu.be/yFFzgANoAXo)

The DPAD buttons switch weapons through emulation of the inventory and action buttons. Weapons should be laid out in inventory from left to bottom, the first 4 weapons will switch to DPAD, the 4th weapon should be used for the sniper rifle. Selecting the 4th weapon is different because it turns on the aiming mode which swaps the stick places, if the sniper rifle is selected through the menu, you can turn on the mode by pressing the right stick. If after selecting the sniper rifle something else is selected through the inventory, then click again on the right stick the mode will be reset.

## Setup
1. Extract [archive](https://github.com/r57zone/RE4ExtendedControl/releases) to the game folder `C:\Games\ResidentEvil4\Bin32` (in the subfolder `Bin32`).
2. If necessary, change the parameters in the `xinput1_3.ini` configuration file. You can disable right stick aiming and quick access to weapons by default, also you can disable them during the game on the keys `ALT + 9` and `ALT + 0`.
3. In the game, go to Settings → Joystick Settings → Xbox 360 Joystick → Button Binding → Type II. If you want to aim only with the right stick, you can turn off the right stick aiming parameter `RightStickAIM=0` in the config and select control type III.
4. In the graphics settings, switch to 60 frames per second.

## Download
>Version for Windows 7, 8.1, 10, 11.

**[Download](https://github.com/r57zone/RE4ExtendedControl/releases)**

## Building
1. Download the sources and unzip them.
2. [Download](https://code.visualstudio.com/download) and [install](https://github.com/r57zone/RE4ExtendedControl/assets/9499881/69dafce6-fd57-4768-83eb-c1bb69901f07) Microsoft Visual Studio Code 2017+.
3. Update the project properties with your tools and SDK.
4. Choose the `Release` build type (if `Debug` is installed) and `x86`, then compile the project.
5. Modify the names of the exported functions by removing the number 2 using [CFF Explorer](https://ntcore.com/?page_id=388).

## Feedback
`r57zone[at]gmail.com`