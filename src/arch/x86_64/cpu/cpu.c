#include <arch/x86_64/cpu/cpu.h>

void outb(uint16_t port, uint8_t value) {
    __asm__ __volatile__ ("outb %%al, %1"  : : "a" (value), "Nd" (port) : "memory");
}

void outw(uint16_t port, uint16_t value) {
    __asm__ __volatile__ ("outw %%ax, %1"  : : "a" (value), "Nd" (port) : "memory");
}

void outd(uint16_t port, uint32_t value) {
    __asm__ __volatile__ ("outl %%eax, %1" : : "a" (value), "Nd" (port) : "memory");
}

uint8_t inb(uint16_t port) {
    uint8_t value;
    __asm__ __volatile__ ("inb %1, %%al"  : "=a" (value) : "Nd" (port) : "memory");
    return value;
}

uint16_t inw(uint16_t port) {
    uint16_t value;
    __asm__ __volatile__ ("inw %1, %%ax"  : "=a" (value) : "Nd" (port) : "memory");
    return value;
}

uint32_t ind(uint16_t port) {
    uint32_t value;
    __asm__ __volatile__ ("inl %1, %%eax" : "=a" (value) : "Nd" (port) : "memory");
    return value;
}