#ifndef GALLERY_CONTROLLER_H
#define GALLERY_CONTROLLER_H

#include "model/AppState.h"
#include "ui/Renderer.h"

class Controller {
    Renderer *renderer;
    // keyboard
    float keyHeldTime = 0.0f;
    int   heldKey     = -1;

    // gamepad
    float padHeldTime = 0.0f;
    int   padHeldDir  = -1;   // 0=up,1=down,2=left,3=right

public:
    Controller(Renderer &renderer);
    void Update(AppState &state);
};

#endif //GALLERY_CONTROLLER_H
