#include <utils/panic.h>
#include <arch/x86_64/cpu/isr.h>

void isr0() { // Divide by 0
    panic("Exception: Division by 0", "EXEC_DIV_0", PANIC_HALT);
}

void isr1() {
    //Impliment Debugging
}

void isr2() { // Non Maskable Interrupt
    panic("Exception: Non-Maskable Interrupt", "EXEC_NMI", PANIC_HALT);
}

void isr3() { // Non Maskable Interrupt
    //Impliment Breakpoints
}

void isr4() { // INTO Overflow
    panic("Exception: INTO Overflow", "EXEC_INTO_OF", PANIC_HALT);
}

void isr5() { // Bound Range Exceeded
    panic("Exception: Bound Range Exceeded", "EXEC_BOUND_EX", PANIC_HALT);
}

void isr6() { // Invalid Opcode
    panic("Exception: Invalid Opcode", "EXEC_INVALID_OP", PANIC_HALT);
}

