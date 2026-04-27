#include "Renderer.h"
#include "Config.h"

void Renderer::DrawTopBar() const {
    DrawText("22:22", 10, 10, 20, theme->Text);
}

void Renderer::LoadInitialTextures() {
    const std::vector<Photo>& photos = imgRepo->GetLibrary();
    const int toLoad = std::min(static_cast<int>(photos.size()), POOL_SIZE);

    for (int i = 0; i < toLoad; i++) {
        // 1. Load img from disk
        Image img = LoadImage(photos[i].path.c_str());

        // Check if loading actually worked
        if (img.data == nullptr) {
            TraceLog(LOG_ERROR, "RENDERER: Failed to load %s", photos[i].path.c_str());
            texturePool[i].photoIndex = -1;
            continue;
        }

        // 2. Make it square
        ImageResizeNN(&img, Config::SLOT_SIZE, Config::SLOT_SIZE);

        // 3. Move to vram
        texturePool[i].texture = LoadTextureFromImage(img);
        texturePool[i].photoIndex = i;
        SetTextureFilter(texturePool[i].texture, TEXTURE_FILTER_POINT);

        TraceLog(LOG_INFO, "RENDERER: Loaded texture ID %u for slot %d", texturePool[i].texture.id, i);

        // 4. Free ram
        UnloadImage(img);
    }
}

void Renderer::DrawLoadingScreen() const {
    DrawTextCentered("LOADING PHOTOS...", Config::SCREEN_H / 2, 30, theme->Accent);
}

void Renderer::DrawPhotoList() {
    constexpr int amount = Config::GRID_COLS * Config::GRID_ROWS;

    for (int i = 0; i < amount; i++) {
        const int column = i % Config::GRID_COLS;
        const int row = i / Config::GRID_COLS;

        const int x = Config::GRID_PAD + (column * (Config::SLOT_SIZE + Config::GRID_PAD));
        const int y = Config::TOPBAR_HEIGHT + Config::GRID_PAD + (row * (Config::SLOT_SIZE + Config::GRID_PAD));

        // 1. Draw Background Panel
        DrawRectangle(x, y, Config::SLOT_SIZE, Config::SLOT_SIZE, theme->Panel);

        // 2. Draw Image (BEFORE the border)
        if (texturePool[i].photoIndex != -1 && texturePool[i].texture.id > 0) {
            DrawTexture(texturePool[i].texture, x, y, WHITE);
        }

        // 3. Draw Selection Border (ON TOP of image)
        if (i == selectedIndex) {
            DrawRectangleLinesEx({(float)x - 4, (float)y - 4, (float)Config::SLOT_SIZE + 8, (float)Config::SLOT_SIZE + 8},
                                 4, theme->Accent);
        }
    }
}

void Renderer::DrawBigPhoto() {
    DrawTextCentered("This is a big photo", Config::SCREEN_H / 2, 30, theme->Accent);
}

void Renderer::DrawDeleteConfirm() {
    DrawTextCentered("Are you sure you want to delete that photo?", Config::SCREEN_H / 2, 30, theme->Accent);
}

void Renderer::DrawTextCentered(const char *text, int y, int fontSize, Color color) {
    const int txtSize = MeasureText(text, fontSize);
    DrawText(text, Config::SCREEN_W / 2 - txtSize / 2, y, fontSize, color);
}

Renderer::Renderer(ImageRepository &imgRepo, DeviceManager &device_manager) {
    theme = &DarkTheme;
    this->device_manager = &device_manager;
    this->imgRepo = &imgRepo;

    // Initialize the pool
    for (int i = 0; i < POOL_SIZE; i++) {
        texturePool[i].photoIndex = -1;
        texturePool[i].texture.id = 0;
    }
}

void Renderer::RenderFrame(AppState &state) {
    BeginDrawing();
    ClearBackground(theme->Bg);
    DrawTopBar();

    switch (state) {
        case Loading:
            DrawLoadingScreen();
            EndDrawing();
            LoadInitialTextures();
            state = PhotoList;
            break;
        case PhotoList: DrawPhotoList();
            break;
        case BigPhoto: DrawBigPhoto();
            break;
        case DeleteConfirm: DrawDeleteConfirm();
            break;
        default: break;
    }

    EndDrawing();
}
