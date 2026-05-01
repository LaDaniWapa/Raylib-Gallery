#ifndef GALLERY_CONTROLLER_H
#define GALLERY_CONTROLLER_H

#include "model/AppState.h"
#include "ui/Renderer.h"

/**
 * @brief Handles user input from keyboard and gamepad.
 *
 * Supports key repeat for both keyboard and gamepad navigation,
 * and translates input into actions on the Renderer and AppState.
 */
class Controller {
    /// Pointer to the renderer for index manipulation
    Renderer *renderer;

    // --- Keyboard ---
    /// Time the current key has been held down
    float keyHeldTime = 0.0f;
    /// Currently held key, -1 if none
    int heldKey = -1;

    // --- Gamepad ---
    /// Time the current gamepad direction has been held
    float padHeldTime = 0.0f;
    /// Currently held direction (0=up, 1=down, 2=left, 3=right), -1 if none
    int padHeldDir = -1;

public:
    /**
     * @brief Constructs the Controller.
     * @param renderer Reference to the renderer to control.
     */
    Controller(Renderer &renderer);

    /**
     * @brief Processes input and updates the application state.
     * @param state Current AppState, may be modified by input.
     */
    void Update(AppState &state);
};

#endif //GALLERY_CONTROLLER_H
