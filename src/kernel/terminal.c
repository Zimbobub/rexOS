#include "terminal.h"

#include <stddef.h>
#include <stdint.h>



Terminal initTerminal(uint8_t rows, uint8_t cols, enum VGAColor foregroundColor, enum VGAColor backgroundColor) {
    Terminal terminal = {
        .buffer=(uint16_t*) 0xB8000,
        .rows=rows,
        .cols=cols,
        .foregroundColor=foregroundColor,
        .backgroundColor=backgroundColor
    };

    return terminal;
}



void putCharAt(Terminal* self, char c, size_t row, size_t col) {
    const size_t index = (self->cols * row) + col;
    // format VGA color (foreground upper 4, background lower 4)
    uint8_t color = (self->foregroundColor | self->backgroundColor << 4);
    // VGA char entry has char in upper 8 bits and color in lower 8
    self->buffer[index] = ((uint16_t) c | (uint16_t) color << 8);
}



void putChar(Terminal* self, char c) {
    putCharAt(self, c, self->currentRow, self->currentCol);

    // move forward 1 char
    self->currentCol++;
    // if at end, go to next row
    if (self->currentCol == self->cols) {
        self->currentRow++;
        self->currentCol = 0;
    }
}



