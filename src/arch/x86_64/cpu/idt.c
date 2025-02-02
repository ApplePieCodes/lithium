#include <arch/x86_64/cpu/idt.h>
#include <arch/x86_64/cpu/isr.h>

extern void idt_load(idt_desc_t *idt_ptr);
extern void isr0_asm();
extern void isr1_asm();
extern void isr2_asm();
extern void isr3_asm();
extern void isr4_asm();
extern void isr5_asm();
extern void isr6_asm();
extern void isr7_asm();
extern void isr8_asm();
extern void isr9_asm();
extern void isr10_asm();
extern void isr11_asm();
extern void isr12_asm();
extern void isr13_asm();
extern void isr14_asm();
extern void isr15_asm();
extern void isr16_asm();
extern void isr17_asm();
extern void isr18_asm();
extern void isr19_asm();

idt_entry_t idt_table[256];

void idt_set_gate(uint16_t num, uint64_t base, uint16_t selector, uint8_t flags) {
    idt_table[num].base0 = base;
    idt_table[num].base1 = (base >> 16) & 0xFFFF;
    idt_table[num].base2 = (base >> 32) & 0xFFFFFFFF;
    idt_table[num].selector = selector;
    idt_table[num].zero = 0;
    idt_table[num].flags = flags;
    idt_table[num].ist = 0;
}

void idt_reload() {
    idt_desc_t idt_table_desc;

    idt_table_desc.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_table_desc.base = (uint64_t)&idt_table;
    
    /* Calls the assembly function to set the IDT */
    idt_load(&idt_table_desc);
}

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
    

    idt_reload();
}