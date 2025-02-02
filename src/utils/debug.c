#include <utils/debug.h>

bool debugger_attached() {
    uint64_t dr6;
    __asm__ __volatile__  ("mov %%dr6, %0" : "=r"(dr6));

    // Check if a debug condition triggered the exception
    return dr6 & 0xF; // Bits 0-3 are set if a hardware breakpoint was hit
}

void handle_debug_event() {
    // Notify debugger or breakpoint handler
}
