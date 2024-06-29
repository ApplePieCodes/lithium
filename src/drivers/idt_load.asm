section .data
    extern idtp

section .text
global idt_load
idt_load:
    lidt [idtp]
    sti
    ret
