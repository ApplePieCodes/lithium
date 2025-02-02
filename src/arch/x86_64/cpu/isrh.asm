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

extern isr3
global isr3_asm
isr3_asm:
    SAVE_REGISTERS
    call isr3
    RESTORE_REGISTERS
    iret

extern isr4
global isr4_asm
isr4_asm:
    SAVE_REGISTERS
    call isr4
    RESTORE_REGISTERS
    iret

extern isr5
global isr5_asm
isr5_asm:
    SAVE_REGISTERS
    call isr5
    RESTORE_REGISTERS
    iret

extern isr6
global isr6_asm
isr6_asm:
    SAVE_REGISTERS
    call isr6
    RESTORE_REGISTERS
    iret

extern isr7
global isr7_asm
isr7_asm:
    SAVE_REGISTERS
    call isr7
    RESTORE_REGISTERS
    iret

extern isr8
global isr8_asm
isr8_asm:
    SAVE_REGISTERS
    call isr8
    RESTORE_REGISTERS
    iret

extern isr9
global isr9_asm
isr9_asm:
    SAVE_REGISTERS
    call isr9
    RESTORE_REGISTERS
    iret

extern isr10
global isr10_asm
isr10_asm:
    SAVE_REGISTERS
    call isr10
    RESTORE_REGISTERS
    iret

extern isr11
global isr11_asm
isr11_asm:
    SAVE_REGISTERS
    call isr11
    RESTORE_REGISTERS
    iret

extern isr12
global isr12_asm
isr12_asm:
    SAVE_REGISTERS
    call isr12
    RESTORE_REGISTERS
    iret

extern isr13
global isr13_asm
isr13_asm:
    SAVE_REGISTERS
    call isr13
    RESTORE_REGISTERS
    iret

extern isr14
global isr14_asm
isr14_asm:
    SAVE_REGISTERS
    call isr14
    RESTORE_REGISTERS
    iret

extern isr15
global isr15_asm
isr15_asm:
    SAVE_REGISTERS
    call isr15
    RESTORE_REGISTERS
    iret

extern isr16
global isr16_asm
isr16_asm:
    SAVE_REGISTERS
    call isr16
    RESTORE_REGISTERS
    iret

extern isr17
global isr17_asm
isr17_asm:
    SAVE_REGISTERS
    call isr17
    RESTORE_REGISTERS
    iret

extern isr18
global isr18_asm
isr18_asm:
    SAVE_REGISTERS
    call isr18
    RESTORE_REGISTERS
    iret

extern isr19
global isr19_asm
isr19_asm:
    SAVE_REGISTERS
    call isr19
    RESTORE_REGISTERS
    iret