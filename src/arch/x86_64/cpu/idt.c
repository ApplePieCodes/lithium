#include <arch/x86_64/cpu/idt.h>
#include <arch/x86_64/cpu/isr.h>

extern void idt_load(idt_desc_t *idt_ptr);
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

    idt_set_gate(0, (uint64_t)isr0, 0x28, 0x8E); // Division by 0
    

    idt_reload();
}