#include "multiboot.h"
#include "stdlib.h"

void kernel_main() {
    while (1) {
        asm volatile ("hlt");
    }
}
