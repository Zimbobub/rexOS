#include "drivers/vga.h"
#include "drivers/serial.h"


extern void main(void) {
    serialInit();

    // terminal cursor position
    size_t row = 0;
    size_t col = 0;


    while (1) {
        if (serialReceived()) {
            char c = serialReadByte();
            VGAPutCharAt(c, row, col, VGA_COLOR_BLACK, VGA_COLOR_WHITE);
            col++;
            if (col == VGA_COLS) {
                row++;
                col = 0;
            }
        }
    }
    
    return;
}
