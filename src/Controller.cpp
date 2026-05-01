#include "Controller.h"
#include <functional>

#include "raylib.h"

int GetActiveGamepad() {
    for (int i = 0; i < 4; i++) {
        if (IsGamepadAvailable(i)) return i;
    }
    return -1; // No gamepad found
}

Controller::Controller(Renderer &renderer) {
    this->renderer = &renderer;
}

void Controller::Update(AppState &state) {
    const int gamepadIdx = GetActiveGamepad();

    if (IsKeyPressed(KEY_ENTER) || gamepadIdx != -1 &&
        IsGamepadButtonPressed(gamepadIdx, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
        switch (state) {
            case Loading:
                state = PhotoList;
                break;
            case PhotoList:
                state = BigPhoto;
                break;
            case BigPhoto:
                state = DeleteConfirm;
                break;
            case DeleteConfirm:
                state = Loading;
        }
    }

    auto handleKey = [&](int key, auto action) {
        if (IsKeyPressed(key)) {
            action();
            heldKey = key;
            keyHeldTime = 0.0f;
        }
        if (heldKey == key) {
            if (IsKeyReleased(key)) {
                heldKey = -1;
            } else if (IsKeyDown(key)) {
                keyHeldTime += GetFrameTime();

                if (keyHeldTime >= Config::REPEAT_DELAY + Config::REPEAT_RATE) {
                    action();
                    keyHeldTime -= Config::REPEAT_RATE;
                }
            }
        }
    };

    handleKey(KEY_DOWN, [&] { renderer->addToIndex(4); });
    handleKey(KEY_UP, [&] { renderer->subtractToIndex(4); });
    handleKey(KEY_RIGHT, [&] { renderer->addToIndex(1); });
    handleKey(KEY_LEFT, [&] { renderer->subtractToIndex(1); });

    if (gamepadIdx != -1) {
        if (IsGamepadButtonPressed(gamepadIdx, GAMEPAD_BUTTON_MIDDLE_RIGHT)) {
            CloseWindow();
            TraceLog(LOG_DEBUG, "====== CLOSE APPLICATION ======");
        }

        const float axisX = GetGamepadAxisMovement(gamepadIdx, GAMEPAD_AXIS_LEFT_X);
        const float axisY = GetGamepadAxisMovement(gamepadIdx, GAMEPAD_AXIS_LEFT_Y);
        int dir = -1;
        std::function<void()> action = nullptr;

        if (IsGamepadButtonDown(gamepadIdx, GAMEPAD_BUTTON_LEFT_FACE_DOWN) ||
            axisY > Config::STICK_DEAD) {
            dir = 1;
            action = [&] { renderer->addToIndex(4); };
        } else if (IsGamepadButtonDown(gamepadIdx, GAMEPAD_BUTTON_LEFT_FACE_UP) ||
                   axisY < -Config::STICK_DEAD) {
            dir = 0;
            action = [&] { renderer->subtractToIndex(4); };
        } else if (IsGamepadButtonDown(gamepadIdx, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ||
                   axisX > Config::STICK_DEAD) {
            dir = 3;
            action = [&] { renderer->addToIndex(1); };
        } else if (IsGamepadButtonDown(gamepadIdx, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ||
                   axisX < -Config::STICK_DEAD) {
            dir = 2;
            action = [&] { renderer->subtractToIndex(1); };
        }

        if (dir != -1 && action != nullptr) {
            if (padHeldDir != dir) {
                action();
                padHeldDir = dir;
                padHeldTime = 0.0f;
            } else {
                padHeldTime += GetFrameTime();
                if (padHeldTime >= Config::REPEAT_DELAY + Config::REPEAT_RATE) {
                    action();
                    padHeldTime -= Config::REPEAT_RATE;
                }
            }
        } else {
            padHeldDir = -1;
            padHeldTime = 0.0f;
        }
    }
}
