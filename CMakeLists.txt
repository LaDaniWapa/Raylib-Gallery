cmake_minimum_required(VERSION 4.2)
project(gallery)

set(CMAKE_CXX_STANDARD 20)

# --- Download and compile raylib ---
include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# Collect all sources
file(GLOB_RECURSE SOURCES src/*.cpp)

# Executable
add_executable(gallery ${SOURCES})

# Include src/ itself
# Point to the root of your source folder
target_include_directories(gallery PRIVATE src)

# If you have an external 'include' folder for 3rd party libs
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
    target_include_directories(gallery PRIVATE include)
endif()

# Debug flags
target_compile_options(gallery PRIVATE -g -fdiagnostics-color)

# Linkear raylib (funciona igual en Linux y Windows)
target_link_libraries(gallery raylib)