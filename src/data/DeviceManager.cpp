#include "DeviceManager.h"
#include "Config.h"
#include <fstream>
#include <ctime>
#include <iomanip>

void DeviceManager::Init() {
    UpdateBattery();
    UpdateTime();
}

const std::string &DeviceManager::GetTime() {
    return this->time;
}

std::string &DeviceManager::GetBattery() {
    return battery;
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
    }
}

void DeviceManager::Update() {
    frameCounter++;

    if (frameCounter % Config::FPS == 0) UpdateTime();
    if (frameCounter % Config::BATTERY_DELAY == 0) UpdateBattery();
    if (frameCounter >= Config::BATTERY_DELAY) frameCounter = 0;
}
