#ifndef MEMORY_HEADER
#define MEMORY_HEADER


#include <malloc.h>


/**
 * Call "malloc" and increase the memory allocation counter.
 */
void *alloc_memory(size_t size);

/**
 * Call "free" and increase the memory deallocation counter.
 */
void free_memory(void *ptr);

/**
 * Check to see if the number of allocations
 * matches the number of frees.
 */
void check_memory();

#endif
