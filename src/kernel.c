#include "vga.h"

void kernel_main() {
    clearScreen(0);
    printString(0, 0, "Hello World!", 15);
}