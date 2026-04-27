#ifndef GALLERY_RENDERER_H
#define GALLERY_RENDERER_H

#include <vector>

#include "data/DeviceManager.h"
#include "data/ImageRepository.h"
#include "model/Photo.h"
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
    static constexpr int POOL_SIZE = 12;
    ThumbnailSlot texturePool[POOL_SIZE];
    Image tmpBuffer{};
    int selectedIndex = 0;

    void DrawTopBar() const;
    void LoadInitialTextures();
    void DrawLoadingScreen() const;
    void DrawPhotoList();
    void DrawBigPhoto();
    void DrawDeleteConfirm();

    static void DrawTextCentered(const char* text, int y, int fontSize, Color color);

public:
    Renderer(ImageRepository &imgRepo, DeviceManager &device_manager);

    void RenderFrame(AppState &state);
};

#endif //GALLERY_RENDERER_H
