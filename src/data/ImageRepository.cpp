#include "ImageRepository.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
#include "raylib.h"

namespace chrono = std::chrono;

bool directoryExists(const std::string &path) {
    struct stat info{};
    return stat(path.c_str(), &info) == 0 && S_ISDIR(info.st_mode);
}

void addDateAndTime(Photo &p, const std::string& path) {
    struct stat info{};
    if (stat(path.c_str(), &info) != 0) return;

    std::tm *lt = std::localtime(&info.st_mtime);

    std::stringstream ssDate;
    ssDate << std::put_time(lt, "%Y-%m-%d");
    p.date = ssDate.str();

    std::stringstream ssTime;
    ssTime << std::put_time(lt, "%H:%M");
    p.time = ssTime.str();
}

void ImageRepository::Init() {
    Scan("/home/daniela/Pictures/test/");
    Scan("/mnt/mmc/MUOS/screenshot/");
}

void ImageRepository::Scan(const std::string &path) {
    TraceLog(LOG_INFO, "SCANNER: Looking for images in %s", path.c_str());

    if (!directoryExists(path)) {
        TraceLog(LOG_ERROR, "SCANNER: Path %s does not exist", path.c_str());
        return;
    }

    DIR *dir = opendir(path.c_str());
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        if (name == "." || name == "..") continue;

        std::string fullPath = path + "/" + name;

        if (entry->d_type == DT_DIR) {
            Scan(fullPath);
        } else {
            auto ext = name.substr(name.find_last_of('.')+1);
            if (ext == "jpg" || ext == "jpeg" || ext == "png") {
                Photo p;
                p.path = fullPath;
                addDateAndTime(p, fullPath);
                library.push_back(p);
            }
        }
    }
    closedir(dir);
    TraceLog(LOG_INFO, "SCANNER: Found %d images", (int) library.size());
}

void ImageRepository::Sort() {
}

std::vector<Photo> ImageRepository::GetLibrary() {
    return this->library;
}

bool ImageRepository::RemovePhoto(std::string path) {
}
