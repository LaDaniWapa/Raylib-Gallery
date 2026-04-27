#include "raylib.h"
#include "Config.h"
#include "Controller.h"
#include "data/ImageRepository.h"
#include "ui/Renderer.h"
#include <filesystem>

namespace fs = std::filesystem;
using namespace Config;

int main() {
    SetTraceLogLevel(LOG_ALL);
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(SCREEN_W, SCREEN_H, "Raylib Gallery Test");
    SetTargetFPS(30);

    Controller controller;
    DeviceManager device_manager;
    ImageRepository imgRepo;
    imgRepo.Scan(fs::path("/home/daniela/Pictures/test/"));
    Renderer renderer(imgRepo, device_manager);

    AppState state = Loading;

    while (!WindowShouldClose()) {
        controller.Update(state);
        renderer.RenderFrame(state);
    }

    CloseWindow();
    return 0;
}
