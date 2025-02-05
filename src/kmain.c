#include <limine.h>
#include <stddef.h>
#include <kmain.h>
#include <memory/pmm.h>
#include <term/term.h>
#include <memory/vmm.h>
#ifdef ARCH_x86_64
#include <arch/x86_64/cpu/gdt.h>
#include <arch/x86_64/cpu/idt.h>
#include <arch/x86_64/dev/timer.h>
#endif


__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests")))
volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
volatile struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
volatile struct limine_kernel_address_request kernel_address_request = {
    .id = LIMINE_KERNEL_ADDRESS_REQUEST,
    .revision = 0
};

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

void kmain() {
    init_term();
    twrite_info("Terminal Initalized");

    #ifdef ARCH_x86_64
    init_timer();
    twrite_info("Initalizing GDT...");
    gdt_init();
    twrite_info("GDT Initalized");
    twrite_info("Initalizing IDT...");
    idt_init();
    twrite_info("IDT Initalized");
    #endif

    twrite_info("Initalizing PMM...");
    pmm_init();
    twrite_info("PMM Initialized");
    twrite_info("Initializing VMM...");
    vmm_init();
    twrite_info("VMM Initialized");


    while (1) {
        
    }
}