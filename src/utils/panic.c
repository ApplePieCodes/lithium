#include <stdbool.h>
#include <utils/halt.h>
#include <utils/panic.h>

void panic(const char *reason, const char *error_code, int option) {
    if (option == PANIC_HALT) {
        halt();
    }
}