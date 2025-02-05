#pragma once

/*
    The Lithium Kernel
    Redistrobution without this header is strictly prohibited. If modifications are made, add your own attribution below.
    @file arch/x86_64/cpu/idt.h
    @author Liam Greenway
*/

#include <stdint.h>
#include <arch/x86_64/cpu/isr.h>

/// @brief IDT Entry
typedef struct idt_entry {
    uint16_t base0;
    uint16_t selector;
    uint8_t ist;
    uint8_t flags;
    uint16_t base1;
    uint32_t base2;
    uint32_t zero;
} __attribute__((packed)) idt_entry_t;

/// @brief Describes the IDT
typedef struct idt_desc {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) idt_desc_t;

/// @brief Initialize the IDT
void idt_init();