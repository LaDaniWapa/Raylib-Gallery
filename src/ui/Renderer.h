#ifndef GALLERY_RENDERER_H
#define GALLERY_RENDERER_H

#include "Config.h"
#include "data/DeviceManager.h"
#include "data/ImageRepository.h"
#include "model/AppState.h"
#include "ui/Theme.h"

struct ThumbnailSlot {
    Texture2D texture{};
    int photoIndex = -1; // Which photo from the library is currently loaded here?
};

class Renderer {
    const ThemePalette *theme;
    DeviceManager *device_manager;
    ImageRepository *imgRepo{};
    static constexpr int POOL_SIZE = Config::GRID_COLS * Config::GRID_ROWS;
    ThumbnailSlot texturePool[POOL_SIZE];
    Image tmpBuffer{};
    int selectedIndex = 0;
    int viewOffset = 0;
    int currentPhotoIndex = 0;

    void LoadInitialTextures();
    void UpdateTexturePool(int currentPhotoIndex);
    void DrawTopBar() const;
    void DrawLoadingScreen() const;
    void DrawPhotoList();
    void DrawBigPhoto();
    void DrawDeleteConfirm();

    static void DrawTextCentered(const char* text, int y, int fontSize, Color color);

public:
    Renderer(ImageRepository &imgRepo, DeviceManager &device_manager);

    void RenderFrame(AppState &state);
    inline void updateIndex(int newIndex);
    int getIndex() const;
    void addToIndex(int amount);
    void subtractToIndex(int amount);
};

#endif //GALLERY_RENDERER_H
