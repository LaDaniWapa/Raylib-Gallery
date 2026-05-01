#ifndef GALLERY_THEME_H
#define GALLERY_THEME_H

#include "raylib.h"

/**
 * @brief Defines the color palette used across the UI.
 */
typedef struct {
    /// Main background color
    Color Bg;
    /// Surface color for panels and cards
    Color Panel;
    /// Background color for selected elements
    Color Select;
    /// Primary text color
    Color Text;
    /// Secondary/dimmed text color
    Color Muted;
    /// Highlight and interactive element color
    Color Accent;
    /// Error and destructive action color
    Color Error;
} ThemePalette;

/// @brief Built-in dark theme palette.
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
