#include <bitset>
#include <conio.h>
#include <iostream>
#include <Windows.h>

static void print_display_device_info(const DISPLAY_DEVICEA& device_res, const DWORD current_counter)
{
    std::cout << "DeviceIndex:" << current_counter << "\n";
    std::cout << "DeviceID:" << device_res.DeviceID << "\n";
    std::cout << "DeviceName:" << device_res.DeviceName << "\n";
    std::cout << "DeviceString:" << device_res.DeviceString << "\n";
    std::cout << "StateFlags:" << device_res.StateFlags << "\n";

    DEVMODEA monitor_props;
    if (EnumDisplaySettingsA(device_res.DeviceName, ENUM_CURRENT_SETTINGS, &monitor_props))
    {
        std::cout << "ResolutionX:" << monitor_props.dmPelsWidth << "\n";
        std::cout << "ResolutionY:" << monitor_props.dmPelsHeight << "\n";
        std::cout << "Frequency:" << monitor_props.dmDisplayFrequency << " Hz" << "\n";
    }
    std::cout << "\n";
}

int main()
{
    DWORD counter = 0;
    DISPLAY_DEVICEA device_res;
    device_res.cb = sizeof(DISPLAY_DEVICEA);
    while (EnumDisplayDevicesA(NULL, counter, &device_res, 0))
    {
        if (device_res.StateFlags & DISPLAY_DEVICE_ACTIVE)
        {
            print_display_device_info(device_res, counter);
        }

        ++counter;
    }

    std::cout << "Press any key to terminate...";
    _getch();
}