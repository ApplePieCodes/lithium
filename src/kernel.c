#include "multiboot.h"
#include "stdlib/stdlib.h"
void kernel_main() {
    terminal_initialize();
    printf("Lithium Kernel v0.1 Loaded\n");
    printf("Thanks, Grub. I'll take it from here.");
    while (1) {
        asm volatile ("hlt");
    }
}
