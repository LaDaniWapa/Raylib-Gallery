#ifndef GALLERY_IMAGEREPOSITORY_H
#define GALLERY_IMAGEREPOSITORY_H

#include <vector>
#include "model/Photo.h"

/**
 * @brief Manages the collection of photos available to the application.
 *
 * Handles scanning directories for images, sorting them, and providing
 * access to the photo library. Also supports photo deletion.
 */
class ImageRepository {
    /// Internal collection of scanned photos
    std::vector<Photo> library;

public:
    /**
     * @brief Initializes the repository and performs the initial scan.
     */
    void Init();

    /**
     * @brief Recursively scans a directory for supported image files.
     * @param path Absolute path to the directory to scan.
     */
    void Scan(const std::string &path);

    /**
     * @todo
     * @brief Sorts the photo library by date, newest first.
     */
    void Sort();

    /**
     * @brief Returns a copy of the photo library.
     * @return Vector containing all scanned Photo objects.
     */
    std::vector<Photo> GetLibrary();

    /**
     *@todo
     * @brief Removes a photo from disk and from the library.
     * @param path Absolute path to the photo to remove.
     * @return True if the photo was successfully removed, false otherwise.
     */
    bool RemovePhoto(std::string path);
};

#endif //GALLERY_IMAGEREPOSITORY_H
