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

void isr7() { // Device not avalible
    panic("Exception: Device Not Avalible", "EXEC_DEVICE_NA", PANIC_HALT);
}

void isr8() { // Double Fault
    panic("Exception: Double Fault", "EXEC_DOUBLE_FLT", PANIC_HALT);
}

void isr9() { // Legacy, unused

}

void isr10() { // Invalid TSS
    panic("Exception: Invalid TSS", "EXEC_INVAlID_TSS", PANIC_HALT);
}

void isr11() {// Invalid Segment
    panic("Exception: Invalid Segment", "EXEC_INVALID_SEG", PANIC_HALT);
}

void isr12() { // Stack Segment Fault
    panic("Exception: Stack Segment Fault", "EXEC_STACK_SEG", PANIC_HALT);
}

void isr13() { // General Protection Fault
    panic("Exception: General Protection Fault", "EXEC_GEN_PROT", PANIC_HALT);
}

void isr14() { // Page Fault
    panic("Exception: Page Fault", "EXEC_PAGE_FAULT", PANIC_HALT);
}

void isr15() { //TODO: Syscall

}

void isr16() { // x87 Floating-Point Exception 
    panic("Exception: x87 Error", "EXEC_X87", PANIC_HALT);
}

void isr17() { // Alignment Check
    panic("Exception: Alignment Check", "EXEC_ALIGN", PANIC_HALT);
}

void isr18() { // Machine Check
    panic("Exception: Hardware Failiure", "EXEC_HW_FAIL", PANIC_HALT);
}

void isr19() { // SIMD Floating-Point
    panic("Exception: SIMD Floating-Point", "EXEC_SIMD_FP", PANIC_HALT);
}