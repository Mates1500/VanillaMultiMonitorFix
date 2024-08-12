# Vanilla Multi Monitor Fix
This is a DLL hook based fix for WoW 1.12 client misbehaving then you have multiple monitors connected with differing supported resolutions.

## Installation
1. Download the most recent release and unzip it to the WoW Folder. 
**TODO: set up github pipelines for automatic release**
2. Set `VMMFix_preferred_monitor.txt`'s contents to your primary WoW monitor identifier, indexed from 0, based on as you see it in Windows. So for monitor 2 in Windows, set 1. For monitor 3, set 2 etc.
3. Add `VanillaMultiMonitorFix.dll` line to `dlls.txt` from the [VanillaFixes](https://github.com/hannesmann/vanillafixes) package to hook it. If you don't already have VanillaFixes, download and install it first. You could also theoretically use the hooking functionality of [wowreeb](https://github.com/namreeb/wowreeb), but I personally haven't tested it.
4. Launch the game through `VanillaFixes.exe` as usual

## Explanation
This is a very simple utility. It hooks the [EnumDisplayDevicesA()](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-enumdisplaydevicesa) WinAPI call by replacing the `iDevNum` argument with your preferred monitor number (until the input number exceeds your monitor device threshold, to avoid endless looping), which means the game will query only that monitor's supported resolution, as the Vanilla client's multi monitor handling with heterogenous resolutions is bad. It shouldn't theoretically break anything, as long as you don't attempt to play the game on a different monitor, but let me know if you encounter anything.

## Build
You can easily build the project yourself in Visual Studio by opening the solution file in `src/`.