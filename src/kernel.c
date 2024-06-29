#include "utils/multiboot.h"
#include "drivers/vga.h"
#include "utils/wait.h"
#include "drivers/idt.h"
#include "drivers/keyboard.h"

void kernel_main() {
    idt_init();
    keyboard_init();
    clearScreen(0);
    
    printLine("Hello World!", 15);
    printLine("This is a new line.", 15);
    printLine("And another line after waiting...", 15);
    wait(50000);
    printLine("Waited 1 second", 15);
    while (1) {
        asm volatile ("hlt");
    }
}
