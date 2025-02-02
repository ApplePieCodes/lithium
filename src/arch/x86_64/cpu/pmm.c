#include <utils/spinlock.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limine.h>
#include <kernel.h>
#include <libc/math.h>
#include <libc/string.h>

static uint8_t *bitmap;
uint64_t highest_address = 0;
uint64_t last_used_index = 0;
uint64_t bitmap_size = 0;
uint64_t free_pages = 0;

lock_t pmm_lock;

void bitmap_set(size_t index) {
    bitmap[index / 8] |= (1 << (index % 8));
}

void bitmap_clear(size_t index)
{
    bitmap[index / 8] &= ~(1 << (index % 8));
}

bool bitmap_get(size_t index)
{
	return bitmap[index / 8] & (1 << (index % 8));
}

void pmm_init() {
    spinlock_lock(&pmm_lock);
    struct limine_memmap_entry **memmap = memmap_request.response->entries;

    uint64_t memmap_entries = memmap_request.response->entry_count;

    for (uint64_t i = 0; i < memmap_entries; i++) {
        if (memmap[i]->type != LIMINE_MEMMAP_USABLE && memmap[i]->type != LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE) {
            continue;
        }

        uint64_t top_address = memmap[i]->base + memmap[i]->length;

        if (top_address > highest_address) {
            highest_address = top_address;
        }
    }
    bitmap_size = ALIGN_UP((highest_address / 4096) / 8, 4096);
    
    for (uint64_t i = 0; i < memmap_entries; i++) {
        if (memmap[i]->type != LIMINE_MEMMAP_USABLE) {
            continue;
        }
        if (memmap[i]->length >= bitmap_size) {
            bitmap = (uint8_t *)(memmap[i]->base + hhdm_request.response->offset);
            memset(bitmap, 0xFF, bitmap_size);
            memmap[i]->length -= bitmap_size;
            memmap[i]->base += bitmap_size;
            break;
        }
    }
}