#include "pch.h"
#include <fstream>
#include <windows.h>
#include <MinHook.h> 
#include <stdexcept>

typedef BOOL(WINAPI* EnumDisplayDevicesA_t)(
    LPCSTR lpDevice, DWORD iDevNum, PDISPLAY_DEVICEA lpDisplayDevice, DWORD dwFlags);

EnumDisplayDevicesA_t OriginalEnumDisplayDevicesA = NULL;

DWORD GetPreferredDisplayIndex()
{
    std::ifstream inputFile("VMMFix_preferred_monitor.txt");

    if (!inputFile) {
        throw std::runtime_error("Error while opening VMMFix_preferred_monitor.txt");
    }

    DWORD value = 0;
    if (!(inputFile >> value)) {
        throw std::runtime_error("Error while parsing VMMFix_preferred_monitor.txt");
    }

    return value;
}

DWORD GetNumberOfDisplayDevices() // needs to be called before hooking EnumDisplayDevicesA(), otherwise it would obviously result in endless recursion/stack overflow
{
    DWORD counter = 0;
    DISPLAY_DEVICEA res;
    res.cb = sizeof(DISPLAY_DEVICEA);
    while (EnumDisplayDevicesA(NULL, counter, &res, 0))
    {
        ++counter;
    }
    return counter;
}

auto const MAX_DISPLAY_DEVICES = GetNumberOfDisplayDevices();
auto const PREFERRED_DISPLAY_INDEX = GetPreferredDisplayIndex();

BOOL WINAPI HookedEnumDisplayDevicesA(LPCSTR lpDevice, DWORD iDevNum, PDISPLAY_DEVICEA lpDisplayDevice, DWORD dwFlags)
{
    if (iDevNum < MAX_DISPLAY_DEVICES)
    {
        return OriginalEnumDisplayDevicesA(lpDevice, PREFERRED_DISPLAY_INDEX, lpDisplayDevice, dwFlags);
    }
    return OriginalEnumDisplayDevicesA(lpDevice, iDevNum, lpDisplayDevice, dwFlags);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (MH_Initialize() != MH_OK)
        {
            return FALSE;
        }

        if (MH_CreateHookApi(L"user32", "EnumDisplayDevicesA", &HookedEnumDisplayDevicesA, 
            reinterpret_cast<LPVOID*>(&OriginalEnumDisplayDevicesA)) != MH_OK)
        {
            return FALSE;
        }

        if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
        {
            return FALSE;
        }
        break;

    case DLL_PROCESS_DETACH:
        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();
        break;
    }
    return TRUE;
}