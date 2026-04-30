#ifndef GALLERY_DEVICEMANAGER_H
#define GALLERY_DEVICEMANAGER_H
#include <string>

#include "Config.h"

class DeviceManager {
    std::string time = "22:22";
    std::string battery = "50";
    int frameCounter = Config::BATTERY_DELAY;

public:
    void Init();
    const std::string &GetTime();
    std::string &GetBattery();
    void Update();
    void UpdateBattery();
    void UpdateTime();
};

#endif //GALLERY_DEVICEMANAGER_H
