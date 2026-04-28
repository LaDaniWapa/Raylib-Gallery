#ifndef GALLERY_CONFIG_H
#define GALLERY_CONFIG_H

namespace Config {
    constexpr int SCREEN_W = 1280;
    constexpr int SCREEN_H = 720;
    constexpr int TOPBAR_HEIGHT = 30;
    constexpr int GAMEPAD = 0;

    constexpr int GRID_COLS = 4;
    constexpr int GRID_ROWS = 2;
    constexpr int GRID_PAD  = 32;  // Space between photos and edges
    constexpr int SLOT_SIZE = 280; // Size of the square photo

    constexpr float STICK_DEAD   = 0.3f;  // dead zone of the stick
    constexpr float REPEAT_DELAY = 0.4f;  // delay before triggering repeat
    constexpr float REPEAT_RATE  = 0.15f; // repeat rate
}

#endif //GALLERY_CONFIG_H
