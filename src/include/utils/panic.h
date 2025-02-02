#pragma once
enum PANIC_OPTION {
    PANIC_REBOOT,
    PANIC_SHUTDOWN,
    PANIC_HALT,
    PANIC_USER_CHOICE
};

void panic(const char *reason, const char *error_code, int option);