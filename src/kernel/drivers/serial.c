#include "serial.h"

#include <stdint.h>
#include "../stdlib/string.h"



// read from an i/o port (1 byte)
uint8_t inb(uint16_t port) {
    uint8_t rv;
    asm volatile ("inb %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

// write to an i/o port (1 byte)
void outb(uint16_t port, uint8_t data) {
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (data));
}

int serialInit() {
    outb(PORT + 1, 0x00);    // Disable all interrupts
    outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(PORT + 1, 0x00);    //                  (hi byte)
    outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    outb(PORT + 4, 0x1E);    // Set in loopback mode, test the serial chip
    outb(PORT + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if(inb(PORT + 0) != 0xAE) {
        return 1;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(PORT + 4, 0x0F);
    return 0;
}


// checks if we have received anything
uint8_t serialReceived() {
    return inb(PORT + 5) & 1;
}
// reads the received message
uint8_t serialReadByte() {
    while (serialReceived() == 0);
 
    return inb(PORT);
}

// checks if we can send a message
uint8_t serialIsTransmitReady() {
    return inb(PORT + 5) & 0x20;
}
// sends a single byte (once ready)
void serialSendByte(char message) {
    while (serialIsTransmitReady() == 0);
 
    outb(PORT, message);
}

void serialSendString(char* message) {
    for (size_t i = 0; i < strlen(message); i++) {
        serialSendByte(message[i]);
    }
}