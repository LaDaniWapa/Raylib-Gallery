#include "DeviceManager.h"
#include "Config.h"
#include <fstream>
#include <ctime>
#include <iomanip>

#include "raylib.h"

void DeviceManager::Init() {
    UpdateBattery();
    UpdateChargingStatus();
    UpdateTime();
}

const std::string &DeviceManager::GetTime() {
    return this->time;
}

std::string &DeviceManager::GetBattery() {
    return battery;
}

bool &DeviceManager::IsCharging() {
    return isCharging;
}

void DeviceManager::UpdateTime() {
    std::time_t now = std::time(nullptr);
    std::tm *lt = std::localtime(&now);
    std::stringstream ss;
    ss << std::put_time(lt, "%H:%M");
    time = ss.str();
}

void DeviceManager::UpdateBattery() {
    std::ifstream ifs(Config::BATTERY_CAPACITY_PATH);
    if (ifs.is_open()) {
        std::getline(ifs, battery);
        ifs.close();
    }
}

void DeviceManager::UpdateChargingStatus() {
    std::ifstream ifs(Config::BATTERY_STATUS_PATH);
    if (ifs.is_open()) {
        std::string status;
        std::getline(ifs, status);
        isCharging = status == "Charging";
        ifs.close();
        TraceLog(LOG_INFO, "Battery status: '%s' (isCharging: %d)", status.c_str(), isCharging);
    } else {
        TraceLog(LOG_ERROR, "Cannot open battery status path: %s", Config::BATTERY_STATUS_PATH);
    }
}

void DeviceManager::Update() {
    frameCounter++;

    if (frameCounter % Config::FPS == 0) {
        UpdateTime();
        UpdateChargingStatus();
    }

    if (frameCounter % Config::BATTERY_DELAY == 0) UpdateBattery();


    if (frameCounter >= Config::BATTERY_DELAY) frameCounter = 0;
}
