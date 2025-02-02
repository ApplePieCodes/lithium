#include <utils/spinlock.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limine.h>
#include <kernel.h>

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
}