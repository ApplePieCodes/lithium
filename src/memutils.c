#include <stddef.h>
#include <stdint.h>
#include "memutils.h"

// Define your memory block structure
typedef struct {
    size_t size;
    unsigned char free;
} mem_block;

size_t detect_available_memory() {
    // Example: Simulate detecting available memory (e.g., read from system information, hardware, etc.)
    return 0x1000000; // Simulated: 16 MB of available memory
}

// Global variables for heap management
void *heap_start = NULL;
void *heap_end = NULL;

// Initialize your memory allocator (heap setup)
void init_allocator(void *start) {
    heap_start = start;
    heap_end = heap_start + 0x1000000;

    // Initialize the first block (entire heap as one block for simplicity)
    mem_block *first_block = (mem_block *)heap_start;
    first_block->size = detect_available_memory() - sizeof(mem_block);
    first_block->free = 1; // Mark as free
}

// Allocate memory from the heap
void *allocate_memory(size_t size) {
    mem_block *curr = (mem_block *)heap_start;
    while (curr != NULL) {
        if (curr->free && curr->size >= size) {
            // Split the block if it's larger than requested size
            if (curr->size > size + sizeof(mem_block)) {
                mem_block *new_block = (mem_block *)((unsigned char *)curr + sizeof(mem_block) + size);
                new_block->size = curr->size - size - sizeof(mem_block);
                new_block->free = 1;

                curr->size = size;
            }
            curr->free = 0;
            return (void *)(curr + 1); // Return pointer just past the block header
        }
        curr = (mem_block *)((unsigned char *)(curr + 1) + curr->size);
    }
    return NULL; // No suitable block found
}

// Free allocated memory
void free_memory(void *ptr) {
    if (ptr == NULL) return;

    mem_block *block = (mem_block *)ptr - 1;
    block->free = 1;

    // Merge adjacent free blocks if possible
    mem_block *curr = (mem_block *)heap_start;
    while (curr != NULL) {
        mem_block *next = (mem_block *)((unsigned char *)(curr + 1) + curr->size);
        if (next >= heap_end || next->free == 0) {
            curr = next;
            continue;
        }

        curr->size += sizeof(mem_block) + next->size;
    }
}
