#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "kk_utilities.h"




static bool kk_init_random_numbers = false;




int kk_random_number(int low, int high)
{
  if (!kk_init_random_numbers) {
    srand(time(NULL));
    kk_init_random_numbers = true;
  }
  return (rand() % (high - low + 1)) + low;
}

