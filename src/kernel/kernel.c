#include "terminal.h"


extern void main(void) {
    // *(char*)0xb8000 = 'Q';


    Terminal terminal = initTerminal(25, 80, VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);

    putCharAt(&terminal, 'Q', 1, 1);



    for (;;);
    return;
}
