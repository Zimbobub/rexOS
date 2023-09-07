#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

#include "../stdlib/string.h"



#define PORT 0x3f8          // COM1




int serialInit();


// checks if we have received anything
uint8_t serialReceived();
// reads the received message
uint8_t serialReadByte();

// checks if we can send a message
uint8_t serialIsTransmitReady();
// sends a single byte (once ready)
void serialSendByte(char message);

void serialSendString(char* message);

#endif