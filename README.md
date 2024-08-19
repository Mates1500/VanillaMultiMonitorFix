# Vanilla Multi Monitor Fix
This is a DLL hook based fix for WoW 1.12 client misbehaving when you have multiple monitors connected with differing supported resolutions.

## Installation
1. Download the most recent [release.zip](https://github.com/Mates1500/VanillaMultiMonitorFix/releases/) and unzip the files to the WoW folder. 
2. Set `VMMFix_preferred_monitor.txt`'s contents to your desired WoW monitor's index, as shown by running `ShowAllDisplayDevices.exe`.
   ![image](https://github.com/user-attachments/assets/eceea532-af2b-448a-8ff6-6d5eb0bea156)

4. Add `VanillaMultiMonitorFix.dll` line to `dlls.txt` from the [VanillaFixes](https://github.com/hannesmann/vanillafixes) package to hook it. If you don't already have VanillaFixes, download and install it first. You could also theoretically use the hooking functionality of [wowreeb](https://github.com/namreeb/wowreeb), but I personally haven't tested it.
5. Launch the game through `VanillaFixes.exe` as usual.

## Explanation
This is a very simple utility. It hooks the [EnumDisplayDevicesA()](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-enumdisplaydevicesa) WinAPI call by replacing the `iDevNum` argument with your preferred monitor number (until the input number exceeds your monitor device threshold, to avoid endless looping), which means the game will query only that monitor's supported resolutions and refresh rates, as the Vanilla client's multi monitor handling with heterogenous resolutions is bad. It shouldn't break anything, as long as you don't attempt to play the game on a different monitor.
## Build
You can build the project yourself in Visual Studio by opening the solution file in `src/`. Remember to clone the project including the submodules using `git clone --recursive {repolink} destPath`
