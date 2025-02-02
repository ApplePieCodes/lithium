OUTPUT(elf64-x86-64)

ENTRY(kmain)

SECTIONS {
    . = 0xffffffff80000000;

    .limine_requests : {
        *(.limine_requests)
    }

    .text : {
        *(.text)
    }
        
    .data : {
        *(.data)
    }
        
    .rodata : {
        *(.rodata)
    }

    .bss : {
        *(.bss)
    }

    KERNEL_END_SYMBOL = .;
}