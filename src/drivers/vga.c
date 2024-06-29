#include "vga.h"

void printLine(const char* str, uint8_t color) {
    int x = 0, y = 0;
    while (*str != '\0') {
        if (x >= VGA_WIDTH) {
            x = 0;
            y++;
        }
        if (y >= VGA_HEIGHT) {
            scrollScreen(color);
            y = VGA_HEIGHT - 1;
        }
        printChar(x, y, *str, color);
        x++;
        str++;
    }
    y++;
}

void printString(int x, int y, const char* str, uint8_t color) {
    while (*str != '\0') {
        if (x >= VGA_WIDTH) {
            x = 0;
            y++;
        }
        if (y >= VGA_HEIGHT) {
            scrollScreen(color);
            y = VGA_HEIGHT - 1;
        }
        printChar(x, y, *str, color);
        x++;
        str++;
    }
}

void printChar(int x, int y, char c, uint8_t color) {
    uint16_t attribute = color << 8;
    uint16_t* vga_memory = (uint16_t*)VGA_BASE;

    vga_memory[y * VGA_WIDTH + x] = c | attribute;
}

void scrollScreen(uint8_t color) {
    uint16_t attribute = color << 8;
    uint16_t* vga_memory = (uint16_t*)VGA_BASE;

    // Move each line up
    for (int y = 1; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_memory[(y - 1) * VGA_WIDTH + x] = vga_memory[y * VGA_WIDTH + x];
        }
    }

    // Clear the last line
    int last_line_index = (VGA_HEIGHT - 1) * VGA_WIDTH;
    for (int x = 0; x < VGA_WIDTH; x++) {
        vga_memory[last_line_index + x] = ' ' | attribute;
    }
}

void clearScreen(uint8_t color) {
    uint16_t attribute = color << 8;
    uint16_t* vga_memory = (uint16_t*)VGA_BASE;

    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i) {
        vga_memory[i] = ' ' | attribute;
    }
}

void setPixel(int x, int y, uint8_t color) {
    uint8_t* vga_memory = (uint8_t*)VGA_BASE;

    int offset = y * VGA_WIDTH + x;
    vga_memory[offset] = color;
}

void clearPixel(int x, int y) {
    setPixel(x, y, 0);
}