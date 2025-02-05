#include <stdbool.h>
#include <utils/halt.h>
#include <utils/panic.h>
#include <libc/stdio.h>
#include <term/term.h>

void panic(const char *reason, const char *error_code, int option) {
    panicex(reason, error_code, "", option);
}

void panicex(const char *reason, const char *error_code, const char *extra_info, int option) {
    //tclear();
    printf("LITHIUM PANIC\nREASON: %s\nERROR CODE: %s\nEXTRA INFO:\n%s", reason, error_code, extra_info);
    if (option == PANIC_HALT) {
        halt();
    }
}