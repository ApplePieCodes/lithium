#include "multiboot.h"
#include "gdt.h"
#include "stdlib/string/string.h"
#include "stdlib/tty.h"
#include "stdlib/stdio/stdio.h"
#include "memutils.h"

void kernel_main() {
    terminal_initialize();
    printf("Lithium Kernel v0.1 Loaded\n");
    printf("Thanks, Grub. I'll take it from here.");
    gdt_init();

    while (1) {
        asm volatile ("hlt");
    }
}
