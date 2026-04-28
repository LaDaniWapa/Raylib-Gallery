cmake_minimum_required(VERSION 3.16)
project(gallery)

set(CMAKE_CXX_STANDARD 20)

# --- Platform detection ---
option(TRIMUI "Build for TRimUI Smart Pro (aarch64)" OFF)

if (TRIMUI)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    set(PLATFORM "SDL" CACHE STRING "" FORCE)
    set(OPENGL_VERSION "ES 2.0" CACHE STRING "" FORCE)
endif ()


# --- Download and compile raylib ---
include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# --- Sources ---
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(gallery ${SOURCES})

# Include src/ itself
target_include_directories(gallery PRIVATE src)

# If you have an external 'include' folder for 3rd party libs
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
    target_include_directories(gallery PRIVATE include)
endif ()

# --- Compile options ---
if (TRIMUI)
    target_compile_options(gallery PRIVATE -O2 -march=armv8-a -mtune=cortex-a53)
else ()
    target_compile_options(gallery PRIVATE -g -fdiagnostics-color)
endif ()

# --- Link ---
if (TRIMUI)
    target_link_libraries(gallery raylib SDL2 atomic m dl pthread stdc++fs)
else ()
    target_link_libraries(gallery raylib)
endif ()