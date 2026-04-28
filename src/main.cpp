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
    SetTargetFPS(30);

    DeviceManager device_manager;
    ImageRepository imgRepo;
    imgRepo.Scan("/home/daniela/Pictures/test/");
    imgRepo.Scan("/mnt/mmc/MUOS/screenshot/");
    Renderer renderer(imgRepo, device_manager);
    Controller controller(renderer);

    AppState state = Loading;

    while (!WindowShouldClose()) {
        controller.Update(state);
        renderer.RenderFrame(state);
    }

    CloseWindow();
    return 0;
}
