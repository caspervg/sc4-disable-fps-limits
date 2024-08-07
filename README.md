# sc4-disable-fps-limits

This DLL plugin for SimCity 4 disables the default FPS (frames per second) limitations during simulation speeds. By default, SimCity 4 imposes the following FPS limits:

- Turtle speed (slow simulation): 30 FPS
- Rhino speed (medium simulation): 20 FPS
- Cheetah speed (fast simulation): 15 FPS

This mod removes these limitations, allowing the game to run at higher frame rates (up to 255 FPS) during all simulation speeds.


The plugin can be downloaded from the Releases tab: https://github.com/caspervg/sc4-disable-fps-limits/releases

## System Requirements

* SimCity 4 version 641
* Windows 10 or later

The plugin may work on Windows 7 or later with the [Microsoft Visual C++ 2022 x86 Redistribute](https://aka.ms/vs/17/release/vc_redist.x86.exe) installed, but I do not have the ability to test that.

## Installation

1. Close SimCity 4.
2. Copy `SC4DisableFpsLimits.dll` into the Plugins folder in the SimCity 4 installation directory.
3. Start SimCity 4.

## Troubleshooting

The plugin should write a `SC4DisableFpsLimits.log` file in the same folder as the plugin.    
The log contains status information for the most recent run of the plugin.

# License

This project is licensed under the terms of the MIT License.    
See [LICENSE.txt](LICENSE.txt) for more information.

## 3rd party code

[gzcom-dll](https://github.com/nsgomez/gzcom-dll/tree/master) Located in the vendor folder, MIT License.    
[EABase](https://github.com/electronicarts/EABase) Located in the vendor folder, BSD 3-Clause License.    
[EASTL](https://github.com/electronicarts/EASTL) Located in the vendor folder, BSD 3-Clause License.    
[SC4Fix](https://github.com/nsgomez/sc4fix) - MIT License.     
[Windows Implementation Library](https://github.com/microsoft/wil) - MIT License

## Credits

A lot of credits go to [Nicholas Hayes](https://github.com/0xC0000054), whose [Disable Demolition Animation](https://github.com/0xC0000054/sc4-disable-demolition-animation) and [Disable Network Construction Sounds](https://github.com/0xC0000054/sc4-disable-network-construction-sounds) DLL mods heavily inspired this one.  

# Source Code

## Prerequisites

* Visual Studio 2022

## Building the plugin

* Open the solution in the `src` folder
* Update the post build events to copy the build output to you SimCity 4 application plugins folder.
* Build the solution

## Debugging the plugin

Visual Studio can be configured to launch SimCity 4 on the Debugging page of the project properties.
I configured the debugger to launch the game in full screen with the following command line:    
`-intro:off -CPUcount:1 -w -CustomResolution:enabled -r1920x1080x32`

You may need to adjust the resolution for your screen.
