#ifndef GALLERY_APPSTATE_H
#define GALLERY_APPSTATE_H

/**
 * @brief Represents the current state of the application.
 */
enum AppState {
    /// Initial state, scanning and loading photos
    Loading,
    /// Browsing the photo grid
    PhotoList,
    /// Viewing a single photo fullscreen
    BigPhoto,
    /// Confirmation dialog before deleting a photo
    DeleteConfirm,
};

#endif //GALLERY_APPSTATE_H
