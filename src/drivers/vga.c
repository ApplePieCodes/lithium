#include "vga.h"

void clearScreen(uint8_t color) {
    uint16_t attribute = color << 8;
    uint16_t* vga_memory = (uint16_t*)VGA_BASE;

    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i) {
        vga_memory[i] = ' ' | attribute;
    }
}

void printChar(int x, int y, char c, uint8_t color) {
    uint16_t attribute = color << 8;
    uint16_t* vga_memory = (uint16_t*)VGA_BASE;

    vga_memory[y * VGA_WIDTH + x] = c | attribute;
}

void setPixel(int x, int y, uint8_t color) {
    uint8_t* vga_memory = (uint8_t*)VGA_BASE;

    int offset = y * VGA_WIDTH + x;
    vga_memory[offset] = color;
}

void clearPixel(int x, int y) {
    setPixel(x, y, 0); // Clear pixel by setting color to 0 (background color)
}

void printString(int x, int y, const char* str, uint8_t color) {
    // Iterate through each character in the string and print it at (x, y)
    while (*str != '\0') {
        printChar(x, y, *str, color);
        x++;
        if (x >= VGA_WIDTH) {
            x = 0;
            y++;
        }
        if (y >= VGA_HEIGHT) {
            clearScreen(color); // If out of screen bounds, clear the screen
            x = 0;
            y = 0;
        }
        str++;
    }
}
