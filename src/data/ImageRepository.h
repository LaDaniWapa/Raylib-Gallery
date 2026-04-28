#ifndef GALLERY_IMAGEREPOSITORY_H
#define GALLERY_IMAGEREPOSITORY_H

#include <vector>
#include "model/Photo.h"

class ImageRepository {
    std::vector<Photo> library;
public:
    bool Init();
    void Scan(const std::string& path);
    void Sort();
    std::vector<Photo> GetLibrary();
    bool RemovePhoto(std::string path);
};

#endif //GALLERY_IMAGEREPOSITORY_H
