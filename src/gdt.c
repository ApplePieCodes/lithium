#include <stdint.h>
#include "gdt.h"

// Definition of the GDT
struct gdt_entry gdt[3] = {
    {0}, // Initialize the first entry to zero
    {0}, // Initialize the second entry to zero
    {0}  // Initialize the third entry to zero
};

// Definition of the GDT pointer
struct gdt_ptr gp = {0};

// Sets up a GDT entry with the specified parameters.
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    // Calculate the base and limit values for the GDT entry.
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    // Combine the base and limit values with the access and granularity flags.
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

// Flushes the GDT to update the CPU's view of the memory segments.
void gdt_flush() {
    // Update the GDT pointer with the current base and limit.
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (uint32_t)&gdt;

    // Use inline assembly to load the GDT into the processor.
    asm volatile("lgdt %0" : : "m"(gp));

    // Reload the segment registers to ensure they reflect the new GDT.
    // Note: This step is crucial for ensuring that the CPU's view of memory segments is updated.
    asm volatile(
        "mov $0x10, %ax;"
        "mov %ax, %ds;"
        "mov %ax, %es;"
        "mov %ax, %fs;"
        "mov %ax, %gs;"
        "mov %ax, %ss;"
    );
}

// Initializes the GDT with the necessary entries for a minimal system.
void gdt_init() {
    // Initialize the GDT with three entries: null, code, and data.
    gdt_set_gate(0, 0, 0, 0, 0);  // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);  // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);  // Data segment

    // Flush the GDT to update the CPU's view of the memory segments.
    gdt_flush();
}