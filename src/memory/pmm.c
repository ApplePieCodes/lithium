#include <utils/spinlock.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limine.h>
#include <kmain.h>
#include <libc/math.h>
#include <libc/string.h>
#include <term/term.h>
#include <memory/pmm.h>
#include <utils/panic.h>
#include <libc/stdio.h>

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
    bitmap_size = ALIGN_UP((highest_address / PAGE_SIZE) / 8, PAGE_SIZE);
    
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

    for (uint64_t i = 0; i < memmap_entries; i++) {
        if (memmap[i]->type != LIMINE_MEMMAP_USABLE) {
            continue;
        }
        for (uint64_t j = 0; j < memmap[i]->length; j += PAGE_SIZE) {
            free_pages++;
            bitmap_clear((memmap[i]->base + j) / PAGE_SIZE);
        }
    }

    spinlock_unlock(&pmm_lock);
}

static void *inner_alloc(uint64_t size, uint64_t limit) {
    uint64_t p = 0;
    while (last_used_index < limit) {
        if(!bitmap_get(last_used_index++))
        {
            if(++p == size)
            {
                uint64_t page = last_used_index - size;
                for(uint64_t i = page; i < last_used_index; i++)
                    bitmap_set(i);
                return (void*) (page * PAGE_SIZE);
            }
        }
        else 
        {
            p = 0;
        }
    }
    return NULL;
}
void* kalloc(uint64_t size)
{
	spinlock_lock(&pmm_lock);
    uint64_t lui = last_used_index;
    void* ret = inner_alloc(size, highest_address / PAGE_SIZE);
    if (ret == NULL)
    {
        last_used_index = 0;
        ret = inner_alloc(size, lui);
        if ( ret == NULL )
        {
            panic("Out Of Memory", "NO_MEMORY", PANIC_HALT);
        }
    }
	free_pages -= size;
	spinlock_unlock(&pmm_lock);
    return ret + hhdm_request.response->offset;
}
void* krealloc(void * ptr, uint64_t old_size, uint64_t new_size)
{
    if (ptr == NULL)
        return kalloc(new_size);

    if(new_size == 0)
    {
        kfree(ptr, old_size);
        return NULL;
    }
    if (new_size < old_size)
        old_size = new_size;

    void* realloc_ptr = kalloc(new_size);
    memcpy(realloc_ptr, ptr, old_size);
    kfree(ptr, old_size);

    return realloc_ptr;
}
void kfree(void * ptr, uint64_t size)
{
	spinlock_lock(&pmm_lock);
    uint64_t page = (uint64_t)ptr / PAGE_SIZE;
    for(uint64_t i = page; i < page + size; i++)
        bitmap_clear(i);
	free_pages += size;
	spinlock_unlock(&pmm_lock);
}

void* kallocz(uint64_t size)
{
    void * ret = kalloc(size);
    uint64_t * ptr = (uint64_t *)ret;

	for (uint64_t i = 0; i < (size * PAGE_SIZE) / 8; i++)
    {
        ptr[i] = 0;
    }

    return ret;
}