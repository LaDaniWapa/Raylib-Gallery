#include "raylib.h"
#include "Config.h"
#include "Controller.h"
#include "data/ImageRepository.h"
#include "ui/Renderer.h"

using namespace Config;

int main() {
    // --- Window setup ---
    SetTraceLogLevel(LOG_ALL);
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_W, SCREEN_H, "Raylib Gallery Test");
    SetTargetFPS(Config::FPS);

    // --- Initialization ---
    DeviceManager device_manager;
    device_manager.Init();

    ImageRepository imgRepo;
    imgRepo.Init();

    Renderer renderer(imgRepo, device_manager);
    Controller controller(renderer);

    AppState state = Loading;

    // --- Main loop ---
    while (!WindowShouldClose()) {
        controller.Update(state);
        device_manager.Update();
        renderer.RenderFrame(state);
    }

    // --- Cleanup ---
    CloseWindow();
    return 0;
}
