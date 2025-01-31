#include <limine.h>
#include <stddef.h>
#ifdef ARCH_x86_64
#include <arch/x86_64/cpu/gdt.h>
#endif

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

void kmain() {
    #ifdef ARCH_x86_64
    gdt_init();
    #endif

    for (;;) {

    }
}