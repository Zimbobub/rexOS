#include "../../kernel/kernel.h"


extern void bootloaderStage2(void) {
    // just to check we made it
    *(char*)0xB8000 = 'Q';
    
    // enter kernel
    kernelMain();
}
