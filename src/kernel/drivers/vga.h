#ifndef VGA_H
#define VGA_H

#include <stddef.h>
#include <stdint.h>

#define VGA_BUFFER ((uint16_t*) 0xB8000)
#define VGA_ROWS 25
#define VGA_COLS 80

void VGAPutCharAt(char c, size_t row, size_t col, uint8_t foregroundColor, uint8_t backgroundColor);

#endif