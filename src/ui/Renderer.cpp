#include "Renderer.h"
#include "Config.h"

void Renderer::LoadInitialTextures() {
    const std::vector<Photo> &photos = imgRepo->GetLibrary();
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
        const float newSize = (float) std::min(img.width, img.height);
        ImageCrop(&img, Rectangle{img.width / 2 - newSize / 2, 0, newSize, newSize});
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

void Renderer::DrawTopBar() const {
    DrawText(TextFormat("%s", device_manager->GetTime().c_str()), 10, 10, 20, theme->Text);
    DrawText(TextFormat("%3s %%", device_manager->GetBattery().c_str()), Config::SCREEN_W - MeasureText("100 %", 20) - 10, 10, 20, theme->Text);
}

void Renderer::UpdateTexturePool(const int currentPhotoIndex) {
    const std::vector<Photo> &photos = imgRepo->GetLibrary();
    const int startIndex = currentPhotoIndex * Config::GRID_COLS;
    ThumbnailSlot nextPool[POOL_SIZE];

    for (int i = 0; i < POOL_SIZE; i++) {
        nextPool[i].photoIndex = -1;
        nextPool[i].texture.id = 0;
    }

    // 1. Transfer visible photos to new pool
    for (int i = 0; i < POOL_SIZE; i++) {
        int oldIndex = texturePool[i].photoIndex;

        if (oldIndex >= startIndex && oldIndex < startIndex + POOL_SIZE) {
            int newSlot = oldIndex - startIndex;
            nextPool[newSlot] = texturePool[i];
            texturePool[i].photoIndex = -1;
            texturePool[i].texture.id = 0;
        }
    }

    // 2. Clear textures
    for (int i = 0; i < POOL_SIZE; i++) {
        if (texturePool[i].texture.id > 0) {
            UnloadTexture(texturePool[i].texture);
        }
    }

    // 3. Load missing photos
    for (int i = 0; i < POOL_SIZE; i++) {
        int globalIndex = startIndex + i;

        if (nextPool[i].photoIndex == -1 && globalIndex < photos.size()) {
            Image img = LoadImage(photos[globalIndex].path.c_str());
            const float newSize = (float) std::min(img.width, img.height);
            ImageCrop(&img, Rectangle{img.width / 2 - newSize / 2, 0, newSize, newSize});
            ImageResizeNN(&img, Config::SLOT_SIZE, Config::SLOT_SIZE);

            nextPool[i].texture = LoadTextureFromImage(img);
            SetTextureFilter(nextPool[i].texture, TEXTURE_FILTER_POINT);
            nextPool[i].photoIndex = globalIndex;

            UnloadImage(img);
            TraceLog(LOG_DEBUG, "POOL: Loaded new texture for index %d", globalIndex);
        }
    }

    // 4. Apply changes
    for (int i = 0; i < POOL_SIZE; i++) {
        texturePool[i] = nextPool[i];
    }
}

void Renderer::DrawLoadingScreen() const {
    DrawTextCentered("LOADING PHOTOS...", Config::SCREEN_H / 2, 30, theme->Accent);
}

void Renderer::DrawPhotoList() {
    const auto &photos = imgRepo->GetLibrary();

    // 1. Determine which row we start drawing from
    const int currentRow = selectedIndex / Config::GRID_COLS;

    // 2. Keep selection on screen
    viewOffset = std::max(0, currentRow - 1);

    // 3. Scroll
    // Scroll down: selection is below us.
    if (currentRow >= currentPhotoIndex + Config::GRID_ROWS) {
        currentPhotoIndex = currentRow - Config::GRID_ROWS + 1;
        UpdateTexturePool(currentPhotoIndex);
    }
    // Scroll up: selection is above us.
    else if (currentRow < currentPhotoIndex) {
        currentPhotoIndex = currentRow;
        UpdateTexturePool(currentPhotoIndex);
    }

    // 4. Draw texture pool
    for (int i = 0; i < POOL_SIZE; i++) {
        // Get actual index in the library
        const int globalIndex = (viewOffset * Config::GRID_COLS) + i;

        // Stop if we reach the end of the library
        if (globalIndex >= photos.size()) break;

        // Calculate screen position (local to the window)
        const int column = i % Config::GRID_COLS;
        const int row = i / Config::GRID_COLS;
        const int x = Config::GRID_PAD + (column * (Config::SLOT_SIZE + Config::GRID_PAD));
        const int y = Config::TOPBAR_HEIGHT + Config::GRID_PAD + (row * (Config::SLOT_SIZE + Config::GRID_PAD));

        // 1. Draw Image
        if (texturePool[i].photoIndex != -1 && texturePool[i].texture.id > 0) {
            DrawTexture(texturePool[i].texture, x, y, WHITE);
        }

        // 2. Draw Selection Border
        if (selectedIndex == texturePool[i].photoIndex) {
            DrawRectangleLinesEx({
                                     (float) x - 4,
                                     (float) y - 4,
                                     (float) Config::SLOT_SIZE + 8,
                                     (float) Config::SLOT_SIZE + 8
                                 },
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

void Renderer::updateIndex(const int newIndex) { selectedIndex = newIndex; }

int Renderer::getIndex() const { return selectedIndex; }

void Renderer::addToIndex(const int amount) {
    const int total = static_cast<int>(imgRepo->GetLibrary().size());
    if (total == 0) return;

    selectedIndex = (selectedIndex + amount + total) % total;
}

void Renderer::subtractToIndex(const int amount) {
    const int total = static_cast<int>(imgRepo->GetLibrary().size());
    if (total == 0) return;

    selectedIndex = (selectedIndex - amount + total) % total;
}
