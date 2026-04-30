#ifndef GALLERY_DEVICEMANAGER_H
#define GALLERY_DEVICEMANAGER_H
#include <string>

#include "Config.h"

class DeviceManager {
    std::string time = "00:00";
    std::string battery = "0";
    bool isCharging = false;
    int frameCounter = Config::BATTERY_DELAY;

public:
    void Init();
    const std::string &GetTime();
    std::string &GetBattery();
    bool &IsCharging();
    void Update();
    void UpdateBattery();
    void UpdateChargingStatus();
    void UpdateTime();
};

#endif //GALLERY_DEVICEMANAGER_H
