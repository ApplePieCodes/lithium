#pragma once

#define PAGE_SIZE 4096

#include <stdint.h>

typedef struct pagemap {
    uint64_t *top_level;
} pagemap_t;

void vmm_init();
void vmm_switch_pagemap(pagemap_t * pagemap);
void vmm_map_page(pagemap_t * pagemap, uint64_t virtual_address, uint64_t physical_address, uint64_t flags);
pagemap_t * vmm_new_pagemap();