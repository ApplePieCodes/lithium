section .data          ; Define a data section (for global/static variables)
    extern idtp        ; Declare idtp as an external symbol

section .text
global idt_load
idt_load:
    lidt [idtp]
    sti
    ret
