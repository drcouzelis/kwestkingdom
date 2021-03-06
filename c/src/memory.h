#ifndef MEMORY_HEADER
#define MEMORY_HEADER


#include <malloc.h>


void show_memory_label();

/**
 * Call "malloc" and increase the memory allocation counter.
 */
void *alloc_memory(const char *label, size_t size);

/**
 * Call "free" and increase the memory deallocation counter.
 */
void free_memory(const char *label, void *ptr);

/**
 * Check to see if the number of allocations
 * matches the number of frees.
 */
void check_memory();


#endif
