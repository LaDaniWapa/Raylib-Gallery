#ifndef GALLERY_RENDERER_H
#define GALLERY_RENDERER_H

#include "Config.h"
#include "data/DeviceManager.h"
#include "data/ImageRepository.h"
#include "model/AppState.h"
#include "ui/Theme.h"

/**
 * @brief Represents a single slot in the texture pool.
 *
 * Each slot holds a thumbnail texture and tracks which photo
 * from the library is currently loaded into it.
 */
struct ThumbnailSlot {
    /// GPU texture for this slot
    Texture2D texture{};
    /// Index into the photo library, -1 if empty
    int photoIndex = -1;
};

/**
 * @brief Handles all rendering logic for the application.
 *
 * Manages a fixed-size texture pool for efficient thumbnail display,
 * and renders different screens depending on the current AppState.
 */
class Renderer {
    /// Active color theme
    const ThemePalette *theme;
    /// Pointer to device manager (battery, time)
    DeviceManager *device_manager;
    /// Pointer to the photo library
    ImageRepository *imgRepo{};
    /// Total number of texture slots
    static constexpr int POOL_SIZE = Config::GRID_COLS * Config::GRID_ROWS;
    /// Fixed pool of GPU textures for thumbnails
    ThumbnailSlot texturePool[POOL_SIZE];
    /// Temporary CPU image buffer for loading
    Image tmpBuffer{};
    /// Currently selected photo index
    int selectedIndex = 0;
    /// Scroll offset in rows
    int viewOffset = 0;
    /// Index of the first photo visible on screen
    int currentPhotoIndex = 0;

    /**
     * @brief Loads the initial set of textures into the pool on startup.
     */
    void LoadInitialTextures();

    /**
    * @brief Updates the texture pool when the user scrolls.
    * @param currentPhotoIndex Index of the first visible photo.
    */
    void UpdateTexturePool(int currentPhotoIndex);

    /// Draws the status bar (time, battery)
    void DrawTopBar() const;

    /// Draws the loading screen
    void DrawLoadingScreen() const;

    /// Draws the photo grid
    void DrawPhotoList();

    /// Draws a single photo fullscreen
    void DrawBigPhoto();

    /// Draws the delete confirmation dialog
    void DrawDeleteConfirm();

    /**
     * @brief Draws text horizontally centered on screen.
     * @param text Text to draw.
     * @param y Vertical position in pixels.
     * @param fontSize Font size.
     * @param color Text color.
     */
    static void DrawTextCentered(const char *text, int y, int fontSize, Color color);

public:
    /**
     * @brief Constructs the Renderer and initializes the texture pool.
     * @param imgRepo Reference to the photo library.
     * @param device_manager Reference to the device manager.
     */
    Renderer(ImageRepository &imgRepo, DeviceManager &device_manager);

    /**
     * @brief Destroys the Renderer and unloads all textures from the GPU.
     */
    ~Renderer();

    /**
     * @brief Renders the current frame based on the application state.
     * @param state Current AppState, may be modified by render logic.
     */
    void RenderFrame(AppState &state);

    /**
     * @brief Sets the selected photo index directly.
     * @param newIndex New index value.
     */
    inline void updateIndex(int newIndex);

    /**
     * @brief Returns the currently selected photo index.
     * @return Current selected index.
     */
    int getIndex() const;

    /**
     * @brief Advances the selected index by the given amount, wrapping around.
     * @param amount Number of positions to advance.
     */
    void addToIndex(int amount);

    /**
     * @brief Moves the selected index back by the given amount, wrapping around.
     * @param amount Number of positions to go back.
     */
    void subtractToIndex(int amount);
};

#endif //GALLERY_RENDERER_H
