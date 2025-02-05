#include <utils/spinlock.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limine.h>
#include <kmain.h>
#include <libc/math.h>
#include <libc/string.h>

#define PAGE_SIZE 4096

void bitmap_set(size_t index);

void bitmap_clear(size_t index);

bool bitmap_get(size_t index);

void pmm_init();

void *kalloc(uint64_t size);
void *krealloc(void * ptr, uint64_t old_size, uint64_t new_size);
void kfree(void * ptr, uint64_t size);
void *kallocz(uint64_t size);