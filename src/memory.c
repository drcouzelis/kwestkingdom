#include <stdio.h>

#include "memory.h"




/**
 * The number of times memory has been allocated.
 */
static int num_alloc = 0;

/**
 * The number of times memory has been freed.
 */
static int num_free = 0;




void *alloc_memory(size_t size)
{
  if (size > 0) {
    num_alloc++;
  }
  
  return malloc(size);
}




void free_memory(void *ptr)
{
  if (ptr != NULL) {
    num_free++;
  }
  
  free(ptr);
}




void check_memory()
{
  if (num_alloc != num_free) {
    fprintf(stderr, "WARNING: alloc: %d free: %d \n", num_alloc, num_free);
  }
}
