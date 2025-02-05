/*
    The Lithium Kernel
    Redistrobution without this header is strictly prohibited. If modifications are made, add your own attribution below.
    @file arch/x86_64/cpu/idt.c
    @author Liam Greenway
*/

#include <arch/x86_64/cpu/idt.h>
#include <arch/x86_64/dev/pic.h>

/// @brief Load the IDT
/// @param idt_ptr Pointer to the IDT Descriptor
extern void idt_load(idt_desc_t *idt_ptr);
/// @brief ISR0
extern void isr0_asm();
/// @brief ISR1
extern void isr1_asm();
/// @brief ISR2
extern void isr2_asm();
/// @brief ISR3
extern void isr3_asm();
/// @brief ISR4
extern void isr4_asm();
/// @brief ISR5
extern void isr5_asm();
/// @brief ISR6
extern void isr6_asm();
/// @brief ISR7
extern void isr7_asm();
/// @brief ISR8
extern void isr8_asm();
/// @brief ISR9
extern void isr9_asm();
/// @brief ISR10
extern void isr10_asm();
/// @brief ISR11
extern void isr11_asm();
/// @brief ISR12
extern void isr12_asm();
/// @brief ISR013
extern void isr13_asm();
/// @brief ISR14
extern void isr14_asm();
/// @brief ISR15
extern void isr15_asm();
/// @brief ISR16
extern void isr16_asm();
/// @brief ISR17
extern void isr17_asm();
/// @brief ISR18
extern void isr18_asm();
/// @brief ISR19
extern void isr19_asm();
extern void irq0_asm();

/// @brief The IDT Table
static idt_entry_t idt_table[256];

/// @brief Sets an IDT gate
/// @param num IDT gate to set
/// @param base Address of the ISR
/// @param selector GDT Segment to run the isr in
/// @param flags Gate type, privilage level, etc.
void idt_set_gate(uint16_t num, uint64_t base, uint16_t selector, uint8_t flags) {
    idt_table[num].base0 = base;
    idt_table[num].base1 = (base >> 16) & 0xFFFF;
    idt_table[num].base2 = (base >> 32) & 0xFFFFFFFF;
    idt_table[num].selector = selector;
    idt_table[num].zero = 0;
    idt_table[num].flags = flags;
    idt_table[num].ist = 0;
}

/// @brief Reload the IDT
void idt_reload() {
    idt_desc_t idt_table_desc;

    idt_table_desc.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_table_desc.base = (uint64_t)&idt_table;
    
    /* Calls the assembly function to set the IDT */
    idt_load(&idt_table_desc);
}

/// @brief Initialize the IDT
void idt_init() {

    idt_set_gate(0, (uint64_t)isr0_asm, 0x28, 0x8E);
    idt_set_gate(1, (uint64_t)isr1_asm, 0x28, 0x8E);
    idt_set_gate(2, (uint64_t)isr2_asm, 0x28, 0x8E);
    idt_set_gate(3, (uint64_t)isr3_asm, 0x28, 0x8E);
    idt_set_gate(4, (uint64_t)isr4_asm, 0x28, 0x8E);
    idt_set_gate(5, (uint64_t)isr5_asm, 0x28, 0x8E);
    idt_set_gate(6, (uint64_t)isr6_asm, 0x28, 0x8E);
    idt_set_gate(7, (uint64_t)isr7_asm, 0x28, 0x8E);
    idt_set_gate(8, (uint64_t)isr8_asm, 0x28, 0x8E);
    idt_set_gate(9, (uint64_t)isr9_asm, 0x28, 0x8E);
    idt_set_gate(10, (uint64_t)isr10_asm, 0x28, 0x8E);
    idt_set_gate(11, (uint64_t)isr11_asm, 0x28, 0x8E);
    idt_set_gate(12, (uint64_t)isr12_asm, 0x28, 0x8E);
    idt_set_gate(13, (uint64_t)isr13_asm, 0x28, 0x8E);
    idt_set_gate(14, (uint64_t)isr14_asm, 0x28, 0x8E);
    idt_set_gate(15, (uint64_t)isr15_asm, 0x28, 0x8E);
    idt_set_gate(16, (uint64_t)isr16_asm, 0x28, 0x8E);
    idt_set_gate(17, (uint64_t)isr17_asm, 0x28, 0x8E);
    idt_set_gate(18, (uint64_t)isr18_asm, 0x28, 0x8E);
    idt_set_gate(19, (uint64_t)isr19_asm, 0x28, 0x8E);

    pic_init();

    idt_set_gate(32, (uint64_t)irq0_asm, 0x28, 0x8E);
    

    idt_reload();
}