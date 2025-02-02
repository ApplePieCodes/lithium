[bits 64]

%macro SAVE_REGISTERS 0
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro RESTORE_REGISTERS 0
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

extern isr0
global isr0_asm
isr0_asm:
    SAVE_REGISTERS
    call isr0
    RESTORE_REGISTERS
    iret

extern isr1
global isr1_asm
isr1_asm:
    SAVE_REGISTERS
    call isr1
    RESTORE_REGISTERS
    iret

extern isr2
global isr2_asm
isr2_asm:
    SAVE_REGISTERS
    call isr2
    RESTORE_REGISTERS
    iret