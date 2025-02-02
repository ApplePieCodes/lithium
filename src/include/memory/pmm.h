#include <utils/spinlock.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limine.h>
#include <kmain.h>
#include <libc/math.h>
#include <libc/string.h>

extern uint8_t *bitmap;

void bitmap_set(size_t index);

void bitmap_clear(size_t index);

bool bitmap_get(size_t index);

void pmm_init();