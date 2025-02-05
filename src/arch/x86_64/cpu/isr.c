/*
    The Lithium Kernel
    Redistrobution without this header is strictly prohibited. If modifications are made, add your own attribution below.
    @file arch/x86_64/cpu/isr.c
    @author Liam Greenway
*/

#include <arch/x86_64/cpu/isr.h>
#include <libc/stdio.h>
#include <arch/x86_64/dev/pic.h>
#include <arch/x86_64/cpu/cpu.h>
#include <arch/x86_64/dev/timer.h>

/// @brief ISR for dividing by 0 exception
void isr0() { // Divide by 0
    panic("Exception: Division by 0", "EXEC_DIV_0", PANIC_HALT);
}

/// @brief ISR for debugging events
void isr1() {
    //Impliment Debugging
}

/// @brief ISR for Non maskable interrupts
void isr2() { // Non Maskable Interrupt
    panic("Exception: Non-Maskable Interrupt", "EXEC_NMI", PANIC_HALT);
}

/// @brief ISR for Breakpoints
void isr3() { // Breakpoint
    //Impliment Breakpoints
}

/// @brief ISR for INTO Overflows
void isr4() { // INTO Overflow
    panic("Exception: INTO Overflow", "EXEC_INTO_OF", PANIC_HALT);
}

/// @brief ISR for Bound Range Exception
void isr5() { // Bound Range Exceeded
    panic("Exception: Bound Range Exceeded", "EXEC_BOUND_EX", PANIC_HALT);
}

/// @brief ISR for invalid Opcode
void isr6() { // Invalid Opcode
    panic("Exception: Invalid Opcode", "EXEC_INVALID_OP", PANIC_HALT);
}

/// @brief ISR for device not avalible
void isr7() { // Device not avalible
    panic("Exception: Device Not Avalible", "EXEC_DEVICE_NA", PANIC_HALT);
}

/// @brief ISR for double fault
void isr8() { // Double Fault
    panic("Exception: Double Fault", "EXEC_DOUBLE_FLT", PANIC_HALT);
}

/// @brief Legacy, does nothing
void isr9() { // Legacy, unused

}

/// @brief ISR for invalid TSS
void isr10() { // Invalid TSS
    panic("Exception: Invalid TSS", "EXEC_INVAlID_TSS", PANIC_HALT);
}

/// @brief ISR for invalid segment
void isr11() {// Invalid Segment
    panic("Exception: Invalid Segment", "EXEC_INVALID_SEG", PANIC_HALT);
}

/// @brief ISR for stack segment fault
void isr12() {
    panic("Exception: Stack Segment Fault", "EXEC_STACK_SEG", PANIC_HALT);
}

/// @brief ISR for general protection fault
void isr13() {
    panic("Exception: General Protection Fault", "EXEC_GEN_PROT", PANIC_HALT);
}

/// @brief ISR for page fault
void isr14(uint64_t error_code) { // Page Fault
    uint64_t faulting_address;

    // Read CR2 (contains the faulting memory address)
    __asm__ volatile("mov %%cr2, %0" : "=r"(faulting_address));

    // Decode the error code
    int present   = (error_code & 0x1) != 0;  // Page not present?
    int write     = (error_code & 0x2) != 0;  // Write operation?
    int user_mode = (error_code & 0x4) != 0;  // Fault in user mode?
    int reserved  = (error_code & 0x8) != 0;  // Reserved bits set?
    int inst_fetch= (error_code & 0x10) != 0; // Instruction fetch?

    char buf[1000];

    sprintf(buf, "Faulting Address: 0x%lx | Error Code: 0x%lx\n - Present: %d | Write: %d | User Mode: %d | Reserved: %d | Inst Fetch: %d", faulting_address, error_code, present, write, user_mode, reserved, inst_fetch);
    panicex("Exception: Page Fault", "EXEC_PAGE_FAULT", buf, PANIC_HALT);
}

/// @brief To-be syscall
void isr15() { //TODO: Syscall

}

/// @brief ISR for x87 Exception
void isr16() { // x87 Floating-Point Exception 
    panic("Exception: x87 Error", "EXEC_X87", PANIC_HALT);
}

/// @brief ISR for alignment check
void isr17() { // Alignment Check
    panic("Exception: Alignment Check", "EXEC_ALIGN", PANIC_HALT);
}

/// @brief ISR for machine check
void isr18() { // Machine Check
    panic("Exception: Hardware Failiure", "EXEC_HW_FAIL", PANIC_HALT);
}

/// @brief ISR for SIMD Exception
void isr19() { // SIMD Floating-Point
    panic("Exception: SIMD Floating-Point", "EXEC_SIMD_FP", PANIC_HALT);
}

void irq0() {
    static int t = 0;
    timer_tick();
    if (t == 0) {
        printf("Tick!");
        t = 1;
    }
    else {
        printf("Tock!");
        t = 0;
    }
    pic_send_eoi(0);   
}