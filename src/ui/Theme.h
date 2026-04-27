#ifndef GALLERY_THEME_H
#define GALLERY_THEME_H

#include "raylib.h"

typedef struct {
    Color Bg;
    Color Panel;
    Color Select;
    Color Text;
    Color Muted;
    Color Accent;
    Color Error;
} ThemePalette;

constexpr ThemePalette DarkTheme = {
    .Bg = {18, 18, 18, 255},
    .Panel = {30, 30, 30, 255},
    .Select = {44, 44, 44, 255},
    .Text = {235, 235, 235, 255},
    .Muted = {160, 160, 160, 255},
    .Accent = {177, 74, 237, 255},
    .Error = {237, 74, 74, 255}
};

#endif //GALLERY_THEME_H
