#include "terminal.h"
#include "drivers/vga.h"



void VGAPutCharAt(char c, size_t row, size_t col, uint8_t foregroundColor, uint8_t backgroundColor) {
    const size_t index = (VGA_COLS * row) + col;
    // format VGA color (foreground upper 4, background lower 4)
    uint8_t color = (foregroundColor | backgroundColor << 4);
    // VGA char entry has char in upper 8 bits and color in lower 8
    // VGA_BUFFER[index] = ((uint16_t) c | (uint16_t) color << 8);
    VGA_BUFFER[index] = ((uint16_t) c | (uint16_t) color << 8);
}





extern void main(void) {
    // *(char*)0xb8000 = 'Q';


    // Terminal terminal = initTerminal(25, 80, VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);

    // putCharAt(&terminal, 'Q', 1, 1);


    VGAPutCharAt('C', 1, 1, VGA_COLOR_BLACK, VGA_COLOR_WHITE);



    return;
}
