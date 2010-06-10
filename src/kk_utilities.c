#include "kk_utilities.h"




static FLAG kk_init_random_numbers = OFF;




int KK_random_number(int low, int high)
{
  if (!kk_init_random_numbers) {
    srand(time(NULL));
    kk_init_random_numbers = ON;
  }
  return (rand() % (high - low + 1)) + low;
}

