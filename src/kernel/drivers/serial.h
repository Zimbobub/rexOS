#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>


#define PORT 0x3f8          // COM1


// read from an i/o port (1 byte)
uint8_t inb(uint16_t port);

// write to an i/o port (1 byte)
void outb(uint16_t port, uint8_t data);


static int init_serial();


// receiving data
int serial_received();
char read_serial();

// sending data
uint8_t is_transmit_empty();
void write_serial(uint8_t a);


#endif