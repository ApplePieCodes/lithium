[bits 64]
global idt_load           ; Allows it to be called from C code
idt_load:
    lidt [rdi]
    ret   