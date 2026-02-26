# SC4 Disable FPS Limits

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

## Configuration

The plugin reads optional settings from `SC4DisableFpsLimits.ini` in the same folder as the DLL.

Example:

```ini
[SC4DisableFpsLimits]
MaxFPS=255
LogLevel=info
```

`MaxFPS` applies to Turtle, Rhino, and Cheetah simulation speeds.
Values above `255` are capped to `255`.
`LogLevel` controls log verbosity and defaults to `info`.
Valid values are `trace`, `debug`, `info`, `warn`, `error`, `critical`, and `off`.

# License

This project is licensed under the terms of the GNU LGPL v2.1 or later.    
See [LICENSE.txt](LICENSE.txt) for more information.

## 3rd party code

[gzcom-dll](https://github.com/nsgomez/gzcom-dll) - GNU LGPL v2.1 or later.    
[SC4Fix](https://github.com/nsgomez/sc4fix) - MIT License.     
[spdlog](https://github.com/gabime/spdlog) - MIT License.    
[mINI](https://github.com/metayeti/mINI) - MIT License.    
[sc4-disable-network-construction-sounds](https://github.com/0xC0000054/sc4-disable-network-construction-sounds) - MIT License (project inspiration).    

## Credits

A lot of credits go to [Nicholas Hayes](https://github.com/0xC0000054), whose [Disable Demolition Animation](https://github.com/0xC0000054/sc4-disable-demolition-animation) and [Disable Network Construction Sounds](https://github.com/0xC0000054/sc4-disable-network-construction-sounds) DLL mods heavily inspired this one.  

# Source Code

## Prerequisites

* CMake 3.24 or newer
* A 32-bit MSVC toolchain (v143 recommended)

## Building the plugin

1. Initialize third-party dependencies:
   * `git submodule update --init --recursive`
2. Configure (Windows x86, Visual Studio):
   * `cmake --preset vs2022-win32`
3. Build:
   * `cmake --build --preset release`

The resulting DLL is at `build/Release/SC4DisableFpsLimits.dll`.

## Cross-compile from macOS/Linux (experimental)

If MinGW-w64 is installed and available in `PATH`, you can attempt a Win32 cross-build:

1. Configure:
   * `cmake --preset mingw-win32-cross`
2. Build:
   * `cmake --build --preset release-mingw`

The MinGW toolchain preset uses:
* [mingw-w64-i686.cmake](/Users/vghelu49/CLionProjects/sc4-disable-fps-limits/cmake/toolchains/mingw-w64-i686.cmake)

## Debugging the plugin

Attach a debugger to the SimCity 4 process or launch it from your debugger with:    
`-intro:off -CPUcount:1 -w -CustomResolution:enabled -r1920x1080x32`

You may need to adjust the resolution for your screen.
