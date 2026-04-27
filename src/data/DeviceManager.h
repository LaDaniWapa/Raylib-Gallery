#ifndef GALLERY_DEVICEMANAGER_H
#define GALLERY_DEVICEMANAGER_H
#include <string>

// Class to fetch system hour and battery

class DeviceManager {
    // todo: Know how to get battery and time info from device

    std::string time = "22:22";
    int battery = 50;

public:
    std::string GetTime();
    int GetBattery();
};

#endif //GALLERY_DEVICEMANAGER_H
