#pragma once

#include <stdint.h>

typedef struct interrupt_frame {
    uint64_t rip;    // Instruction Pointer
    uint64_t cs;     // Code Segment
    uint64_t rflags; // CPU Flags
    uint64_t rsp;    // Stack Pointer
    uint64_t ss;     // Stack Segment
} interrupt_frame_t;

void isr0();
void isr1();
void isr2();
void isr3();
void isr4();
void isr5();
void isr6();
void isr7();
void isr8();
void isr9();
void isr10();
void isr11();
void isr12();
void isr13();
void isr14();
void isr15();
void isr16();
void isr17();
void isr18();
void isr19();