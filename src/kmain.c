#include <limine.h>
#include <stddef.h>
#include <kmain.h>
#include <memory/pmm.h>
#include <../term/flanterm.h>
#include <../term/backends/fb.h>
#ifdef ARCH_x86_64
#include <arch/x86_64/cpu/gdt.h>
#include <arch/x86_64/cpu/idt.h>
#endif


__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(3);

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

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
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

void kmain() {
    /*if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
        for (;;) __asm__("hlt");
    }*/

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    struct flanterm_context *ft_ctx = flanterm_fb_init(NULL,NULL,framebuffer->address,framebuffer->width, framebuffer->height, framebuffer->pitch, framebuffer->red_mask_size, framebuffer->red_mask_shift, framebuffer->green_mask_size, framebuffer->green_mask_shift, framebuffer->blue_mask_size, framebuffer->blue_mask_shift, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15, 15, 5, 5, 5, 0);

    flanterm_write(ft_ctx, "Hello, World!\n", 15);

    /*#ifdef ARCH_x86_64
    gdt_init();
    idt_init();
    #endif

    //pmm_init();*/

    while (1) {

    }
}