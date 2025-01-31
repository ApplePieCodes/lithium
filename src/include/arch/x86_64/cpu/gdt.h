#pragma once

#include <stdint.h>

typedef struct gdt_entry_t{
    uint16_t limit;
    uint16_t base0;
    uint8_t base1;
    uint8_t access;
    uint8_t granularity;
    uint8_t base2;   
} __attribute__((packed)) gdt_entry_t;

typedef struct tss_desc
{
    uint16_t limit;
    uint16_t base0;
    uint8_t base1;
    uint8_t access;
    uint8_t flags;
    uint8_t base2;
    uint32_t base3;
    uint32_t reserved;
} __attribute__((packed)) tss_desc_t;

typedef struct gdt_desc
{
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) gdt_desc_t;

typedef struct gdt{
    gdt_entry_t null;
    gdt_entry_t code_16;
    gdt_entry_t data_16;
    gdt_entry_t code_32;
    gdt_entry_t data_32;
    gdt_entry_t code_64;
    gdt_entry_t data_64;
    gdt_entry_t user_code_64;
    gdt_entry_t user_data_64;
    tss_desc_t tss;
} __attribute__((packed)) gdt_t;

typedef struct tss {
    uint32_t reserved0;
    uint64_t rsp0;
    uint64_t rsp1;
    uint64_t rsp2;
    uint64_t reserved1_2;
    uint64_t ist1;
    uint64_t ist2;
    uint64_t ist3;
    uint64_t ist4;
    uint64_t ist5;
    uint64_t ist6;
    uint64_t ist7;
    uint64_t reserved3_4;
    uint16_t reserved5;
    uint16_t IOPB;
} __attribute__((packed)) tss_t;

static gdt_t gdt_table;
static tss_t tss_table;

void gdt_init();