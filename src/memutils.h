#ifndef MEMUTILS_H
#define MEMUTILS_H

#include <stddef.h>

void init_allocator(void *start, size_t size);
void *allocate_memory(size_t size);
void free_memory(void *ptr);

#endif