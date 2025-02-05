#include <memory/vmm.h>
#include <stdint.h>
#include <kmain.h>
#include <memory/pmm.h>
#include <libc/stdio.h>
#include <utils/panic.h>

extern char KERNEL_END_SYMBOL[];

pagemap_t kernel_pagemap;

uint64_t get_kernel_end_addr() {
    return (uint64_t)KERNEL_END_SYMBOL;
}

static uint64_t *get_next_level(uint64_t *current_level, uint64_t entry) {
    if (!current_level) {
        panic("get_next_level: current_level is NULL", "", PANIC_HALT);
    }

    if (entry >= 512) { // Validate entry
        panic("get_next_level: entry index out of bounds", "", PANIC_HALT);
    }

    uint64_t *ret;
    if (current_level[entry] & 1) {
        ret = (uint64_t *)(current_level[entry] & ~((uint64_t)0xFFF));
    } else {
        ret = kallocz(1);
        if (!ret) {
            panic("get_next_level: kallocz failed", "", PANIC_HALT);
        }
        current_level[entry] = (uint64_t)ret | 0b1111;
    }

    return ret;
}


void vmm_map_page(pagemap_t *pagemap, uint64_t virtual_address, uint64_t physical_address, uint64_t flags) {
    uint64_t pagemap_entry_4 = (virtual_address >> 39) & 0x1FF;
    uint64_t pagemap_entry_3 = (virtual_address >> 30) & 0x1FF;
    uint64_t pagemap_entry_2 = (virtual_address >> 21) & 0x1FF;
    uint64_t pagemap_entry_1 = (virtual_address >> 12) & 0x1FF;

    uint64_t *pagemap_level_4 = pagemap->top_level;
    uint64_t *pagemap_level_3 = get_next_level(pagemap_level_4, pagemap_entry_4);
    uint64_t *pagemap_level_2 = get_next_level(pagemap_level_3, pagemap_entry_3);
    uint64_t *pagemap_level_1 = get_next_level(pagemap_level_2, pagemap_entry_2);

    pagemap_level_1[pagemap_entry_1] = physical_address | flags;
}

void vmm_init() {
    if (!kernel_address_request.response) {
        panic("kernel_address_request is NULL", "", PANIC_HALT);
    }
    if (!hhdm_request.response) {
        panic("hhdm_request is NULL", "", PANIC_HALT);
    }
    if (!memmap_request.response) {
        panic("memmap_request is NULL", "", PANIC_HALT);
    }

    kernel_pagemap.top_level = kallocz(1);
    if (!kernel_pagemap.top_level) {
        panic("Failed to allocate kernel_pagemap top level", "", PANIC_HALT);
    }

    for (uint64_t i = 256; i < 512; i++) {
        get_next_level(kernel_pagemap.top_level, i);
    }

    /*uint64_t virt = kernel_address_request.response->virtual_base;
    uint64_t phys = kernel_address_request.response->physical_base;
    uint64_t len = ALIGN_UP(get_kernel_end_addr(), PAGE_SIZE) - virt;

    for (uint64_t j = 0; j < len; j += PAGE_SIZE) {
        vmm_map_page(&kernel_pagemap, virt + j, phys + j, 0x04);
    }

    for (uint64_t i = 0x1000; i < 0x100000000; i += PAGE_SIZE) {
        vmm_map_page(&kernel_pagemap, i, i, 0x04);
        vmm_map_page(&kernel_pagemap, i + hhdm_request.response->offset, i, 0x04);
    }

    for (uint64_t i = 0; i < memmap_request.response->entry_count; i++) {
        uint64_t base = ALIGN_DOWN(memmap_request.response->entries[i]->base, PAGE_SIZE);
        uint64_t top = ALIGN_UP(memmap_request.response->entries[i]->base + memmap_request.response->entries[i]->length, PAGE_SIZE);
        if (top <= 0x100000000) {
            continue;
        }
        for (uint64_t j = base; j < top; j += PAGE_SIZE) {
            if (j < 0x100000000) {
                continue;
            }
            vmm_map_page(&kernel_pagemap, j, j, 0x04);
            vmm_map_page(&kernel_pagemap, j + hhdm_request.response->offset, j, 0x04);
        }
    }

    printf("Switching to new pagemap: %p\n", kernel_pagemap.top_level);
    vmm_switch_pagemap(&kernel_pagemap);*/
}

void vmm_switch_pagemap(pagemap_t *pagemap) {
    if (!pagemap || !pagemap->top_level) {
        panic("Invalid pagemap in vmm_switch_pagemap()", "", PANIC_HALT);
    }
    printf("Switching CR3 to: %p\n", pagemap->top_level);
    __asm__ __volatile__("mov %0,%%cr3" : : "r"(pagemap->top_level) : "memory");
}

pagemap_t *vmm_new_pagemap() {
    pagemap_t *map = kalloc(sizeof(pagemap_t));
    if (!map) {
        panic("Failed to allocate new pagemap", "", PANIC_HALT);
    }

    map->top_level = kallocz(1);
    if (!map->top_level) {
        panic("Failed to allocate new pagemap top level", "", PANIC_HALT);
    }

    for (size_t i = 256; i < 512; i++) {
        map->top_level[i] = kernel_pagemap.top_level[i];
    }
    return map;
}
