#include <stdbool.h>

void panic(const char *reason, const char *error_code, int option) {
    if (option == PANIC_HALT) {
        halt();
    }
}

void halt() {
    __asm__ __volatile__ ("cli");
    while (true) {

    }
}