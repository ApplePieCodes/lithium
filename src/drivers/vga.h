#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define VGA_BASE 0xA0000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void clearScreen(uint8_t color);
void printChar(int x, int y, char c, uint8_t color);
void setPixel(int x, int y, uint8_t color);
void clearPixel(int x, int y);
void printString(int x, int y, const char* str, uint8_t color);

#endif // VGA_H
