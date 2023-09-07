#include "vga.h"

#include <stddef.h>
#include <stdint.h>
// #include "string.h"



void VGAPutCharAt(char c, size_t row, size_t col, uint8_t foregroundColor, uint8_t backgroundColor) {
    const size_t index = (VGA_COLS * row) + col;
    // format VGA color (foreground upper 4, background lower 4)
    uint8_t color = (foregroundColor | backgroundColor << 4);
    // VGA char entry has char in upper 8 bits and color in lower 8
    // VGA_BUFFER[index] = ((uint16_t) c | (uint16_t) color << 8);
    VGA_BUFFER[index] = ((uint16_t) c | (uint16_t) color << 8);
}



void VGAPutString(char* s, uint8_t row, uint8_t col, uint8_t foregroundColor, uint8_t backgroundColor) {
    return;
}
