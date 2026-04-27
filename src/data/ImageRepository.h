#ifndef GALLERY_IMAGEREPOSITORY_H
#define GALLERY_IMAGEREPOSITORY_H

#include <vector>
#include <filesystem>
#include "model/Photo.h"

namespace fs = std::filesystem;

class ImageRepository {
    std::vector<Photo> library;
public:
    bool Init();
    void Scan(fs::path path);
    void Sort();
    std::vector<Photo> GetLibrary();
    bool RemovePhoto(std::string path);
};

#endif //GALLERY_IMAGEREPOSITORY_H
