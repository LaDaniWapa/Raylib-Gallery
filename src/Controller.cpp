#include "Controller.h"
#include "raylib.h"

int GetActiveGamepad() {
    for (int i = 0; i < 4; i++) {
        if (IsGamepadAvailable(i)) return i;
    }
    return -1; // No gamepad found
}

void Controller::Update(AppState &state) {
    int gamepadIdx = GetActiveGamepad();

    // Example logic: Pressing ENTER or the Gamepad 'A' button
    if (IsKeyPressed(KEY_ENTER) || gamepadIdx != -1 && IsGamepadButtonPressed(gamepadIdx, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
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
}
