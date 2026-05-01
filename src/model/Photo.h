#ifndef GALLERY_PHOTO_H
#define GALLERY_PHOTO_H

#include <string>

/**
 * @brief Represents a single photo and its metadata.
 */
typedef struct {
    /// Absolute path to the image file on disk
    std::string path;
    /// Date the photo was taken or modified (YYYY-MM-DD)
    std::string date;
    /// Time the photo was taken or modified (HH:MM)
    std::string time;
} Photo;

#endif //GALLERY_PHOTO_H
