#ifndef GDT_H
#define GDT_H

#include <stdint.h>

struct gdt_entry {
    uint16_t limit_low;     // The lower 16 bits of the limit
    uint16_t base_low;      // The lower 16 bits of the base
    uint8_t base_middle;    // The next 8 bits of the base
    uint8_t access;         // Access flags, determine the type of segment
    uint8_t granularity;    // Granularity and limit flags
    uint8_t base_high;      // The last 8 bits of the base
} __attribute__((packed));

// Pointer to the GDT
struct gdt_ptr {
    uint16_t limit;         // Limit of the GDT
    uint32_t base;          // Base address of the GDT
} __attribute__((packed));

// Define a GDT with 3 entries: null, code, data
extern struct gdt_entry gdt[3];
extern struct gdt_ptr gp;

void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void gdt_flush();
void gdt_init();

#endif // GDT_H