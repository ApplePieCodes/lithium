#include <stdint.h>
#include <arch/x86_64/dev/timer.h>
#include <arch/x86_64/cpu/cpu.h>

void init_timer() {
    int32_t divisor = 1193180 / TIMER_HZ;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
}

void timer_tick() {
    timer_ticks++;
}