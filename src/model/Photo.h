#ifndef GALLERY_PHOTO_H
#define GALLERY_PHOTO_H

#include <string>

// Data class holding path, date and time
typedef struct {
    std::string path;
    std::string date;
    std::string time;
} Photo;

#endif //GALLERY_PHOTO_H
