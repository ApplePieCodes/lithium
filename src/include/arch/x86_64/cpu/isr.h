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