#include <arch/x86_64/cpu/gdt.h>

static gdt_t gdt_table;

void gdt_reload()
{
    gdt_desc_t gdt_descriptor;

    gdt_descriptor.limit = sizeof(gdt_t) - 1;
    gdt_descriptor.base = (uint64_t)&gdt_table;

    __asm__ __volatile__ ("lgdt %0" : : "m"(gdt_descriptor) : "memory");
}
void tss_reload()
{
    __asm__ __volatile__ ("ltr %0" : : "r" ((uint16_t)0x48));
}

static tss_t tss_table;

void gdt_init() {
    gdt_table = (gdt_t){
        // Null Segment
        .null = (gdt_entry_t){
            .limit = 0x0000,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b00000000,
            .granularity = 0b00000000,
            .base2 = 0x00
        },
        // 16-Bit Code Segment
        .code_16 = (gdt_entry_t){
            .limit = 0xFFFF,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b10011010,
            .granularity = 0b00000000,
            .base2 = 0x00
        },
        // 16-Bit Data Segment
        .data_16 = (gdt_entry_t){
            .limit = 0xFFFF,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b10010010,
            .granularity = 0b00000000,
            .base2 = 0x00
        },
        // 32-Bit Code Segment
        .code_32 = (gdt_entry_t){
            .limit = 0xFFFF,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b10011010,
            .granularity = 0b11001111,
            .base2 = 0x00
        },
        // 32-Bit Data Segment
        .data_32 = (gdt_entry_t){
            .limit = 0xFFFF,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b10010010,
            .granularity = 0b11001111,
            .base2 = 0x00
        },
        // 64-Bit Code Segment
        .code_64 = (gdt_entry_t){
            .limit = 0x0000,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b10011010,
            .granularity = 0b00100000,
            .base2 = 0x00
        },
        // 64-Bit Data Segment
        .data_64 = (gdt_entry_t){
            .limit = 0x0000,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b10010010,
            .granularity = 0b00000000,
            .base2 = 0x00
        },
        // 64-Bit User Code Segment
        .user_code_64 = (gdt_entry_t){
            .limit = 0x0000,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b11111010,
            .granularity = 0b00000000,
            .base2 = 0x00
        },
        // 64-Bit User Data Segment
        .user_data_64 = (gdt_entry_t){
            .limit = 0x0000,
            .base0 = 0x0000,
            .base1 = 0x00,
            .access = 0b11110010,
            .granularity = 0b00100000,
            .base2 = 0x00
        },
        // TSS Segment
        .tss = (tss_desc_t){
            .limit = ((uint64_t)&tss_table) + sizeof(tss_table),
            .base0 = ((uint64_t)&tss_table),
            .base1 = ((uint64_t)&tss_table) >> 16,
            .access = 0x89,
            .flags = 0x00,
            .base2 = ((uint64_t)&tss_table) >> 24,
            .base3 = ((uint64_t)&tss_table) >> 32,
            .reserved = 0x00
        }
    };
    
    gdt_reload();
    tss_reload();
}