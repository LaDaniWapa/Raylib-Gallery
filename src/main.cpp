#include "raylib.h"
#include "Config.h"
#include "Controller.h"
#include "data/ImageRepository.h"
#include "ui/Renderer.h"

using namespace Config;

int main() {
    SetTraceLogLevel(LOG_ALL);
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_W, SCREEN_H, "Raylib Gallery Test");
    SetTargetFPS(Config::FPS);

    DeviceManager device_manager;
    device_manager.Init();

    ImageRepository imgRepo;
    imgRepo.Scan("/home/daniela/Pictures/test/");
    imgRepo.Scan("/mnt/mmc/MUOS/screenshot/");

    Renderer renderer(imgRepo, device_manager);

    Controller controller(renderer);

    AppState state = Loading;

    while (!WindowShouldClose()) {
        controller.Update(state);
        device_manager.Update();
        renderer.RenderFrame(state);
    }

    CloseWindow();
    return 0;
}
