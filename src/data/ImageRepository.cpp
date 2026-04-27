#include "ImageRepository.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include "raylib.h"

namespace chrono = std::chrono;

void addDateAndTime(Photo &p, fs::file_time_type ftime) {
    auto sctp = chrono::time_point_cast<chrono::system_clock::duration>(
        ftime - fs::file_time_type::clock::now() + chrono::system_clock::now()
    );
    std::time_t cftime = chrono::system_clock::to_time_t(sctp);
    std::tm *lt = std::localtime(&cftime);

    std::stringstream ssDate;
    ssDate << std::put_time(lt, "%Y-%m-%d");
    p.date = ssDate.str();

    std::stringstream ssTime;
    ssTime << std::put_time(lt, "%H:%M");
    p.time = ssTime.str();
}

bool ImageRepository::Init() {
    return true;
}

void ImageRepository::Scan(fs::path path) {
    TraceLog(LOG_INFO, "SCANNER: Looking for images in %s", path.string().c_str());

    for (const auto &entry: fs::recursive_directory_iterator(path, fs::directory_options::follow_directory_symlink)) {
        if (!entry.is_regular_file()) continue;

        // Get the extension and make it lowercase
        std::string ext = entry.path().extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

        // Check for both JPG and PNG
        if (ext == ".jpg" || ext == ".jpeg" || ext == ".png") {
            Photo p;
            p.path = entry.path().string();
            addDateAndTime(p, entry.last_write_time());
            library.push_back(p);
        }
    }

    TraceLog(LOG_INFO, "SCANNER: Found %d images", (int)library.size());
}

void ImageRepository::Sort() {
}

std::vector<Photo> ImageRepository::GetLibrary() {
    return this->library;
}

bool ImageRepository::RemovePhoto(std::string path) {
}
