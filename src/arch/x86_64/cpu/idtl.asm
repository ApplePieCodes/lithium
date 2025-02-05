;
;   The Lithium Kernel
;   Redistrobution without this header is strictly prohibited. If modifications are made, add your own attribution below.
;   @file arch/x86_64/cpu/idtl.asm
;   @author Liam Greenway
;

[bits 64]
global idt_load           ; Allows it to be called from C code
; Load the IDT
idt_load:
    lidt [rdi]
    ret