#ifndef GALLERY_DEVICEMANAGER_H
#define GALLERY_DEVICEMANAGER_H

#include <string>
#include "Config.h"

/**
 * @brief Manages device hardware information such as battery and time
 *
 * Reads battery capacity, charging status and current time from the system,
 * updating them periodically to avoid unnecessary I/O every frame.
 */
class DeviceManager {
    /// Current time in HH:MM format
    std::string time = "00:00";
    /// Battery capacity in %
    std::string battery = "0";
    /// Is the device currently charging?
    bool isCharging = false;
    /// Frame counter for throttling battery reads
    int frameCounter = Config::BATTERY_DELAY;

public:
    /**
     * @brief Initializes the DeviceManager, performing an immediate read of all values.
     */
    void Init();

    /**
    * @brief Returns the current time string.
    * @return Reference to the time string in HH:MM format.
    */
    const std::string &GetTime();

    /**
     * @brief Returns the current battery level.
     * @return Reference to the battery capacity string (e.g. "85").
     */
    std::string &GetBattery();

    /**
    * @brief Returns the current charging status.
    * @return Reference to the isCharging flag.
    */
    bool &IsCharging();

    /**
     * @brief Called every frame. Throttles and dispatches hardware reads.
     */
    void Update();

    /**
    * @brief Reads battery capacity from the system power supply interface.
    */
    void UpdateBattery();

    /**
     * @brief Reads charging status from the system power supply interface.
     */
    void UpdateChargingStatus();

    /**
    * @brief Updates the current time from the system clock.
    */
    void UpdateTime();
};

#endif //GALLERY_DEVICEMANAGER_H
