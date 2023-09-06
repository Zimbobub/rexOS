#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>
#include <stdint.h>


/* text mode colors */
enum VGAColor {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

// silences some warning about referencing Terminal in the methods before its defined
struct Terminal;

typedef struct {
    uint8_t rows;
    uint8_t cols;

    size_t currentRow;
    size_t currentCol;

    uint16_t* buffer;
    uint8_t foregroundColor;
    uint8_t backgroundColor;

} Terminal;

Terminal initTerminal(uint8_t rows, uint8_t cols, enum VGAColor foregroundColor, enum VGAColor backgroundColor);
void putCharAt(Terminal* self, char c, size_t row, size_t col);
void putChar(Terminal* self, char c);

#endif