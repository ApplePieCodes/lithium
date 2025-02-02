#include <utils/panic.h>

void isr0() { // Divide by 0
    panic("Exception: Division by 0", "EXEC_DIV_0", PANIC_USER_CHOICE);
}