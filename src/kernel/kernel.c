#include "drivers/vga.h"
#include "drivers/serial.h"


extern void main(void) {
    VGAPutCharAt('C', 1, 1, VGA_COLOR_BLACK, VGA_COLOR_WHITE);



    return;
}
