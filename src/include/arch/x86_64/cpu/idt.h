#pragma once

#include <stdint.h>

typedef struct idt_entry {
    uint16_t base0;
    uint16_t selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t base1;
    uint32_t base2;
    uint32_t zero;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_desc {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) idt_desc_t;

void idt_init();