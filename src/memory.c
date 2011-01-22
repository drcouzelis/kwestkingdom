#include <stdio.h>

#include "memory.h"
#include "utilities.h"




/**
 * The number of times memory has been allocated.
 */
static int num_alloc = 0;

/**
 * The number of times memory has been freed.
 */
static int num_free = 0;

/**
 * Whether or not to show the label.
 */
FLAG show_label = OFF;




void show_memory_label()
{
  show_label = ON;
}




void *alloc_memory(const char *label, size_t size)
{
  if (size > 0) {

  	if (show_label) {
   	  printf("ALLOC %s \n", label);
  	}

    num_alloc++;
  }
  
  return malloc(size);
}




void free_memory(const char *label, void *ptr)
{
  if (ptr != NULL) {

  	if (show_label) {
      printf("FREE %s \n", label);
  	}

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
