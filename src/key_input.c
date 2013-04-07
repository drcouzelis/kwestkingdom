#include <allegro.h>

#include "key_input.h"
#include "utilities.h"


static FLAG key_held[KEY_MAX];
static FLAG key_init = OFF;


void init_keys()
{
  int i;

  if (key_init) {
    return;
  }

  for (i = 0; i < KEY_MAX; i++) {
    key_held[i] = OFF;
  }

  key_init = ON;
}


FLAG is_key_pressed(char key_code)
{
    init_keys();
    
    if (!key_held[key_code] && key[key_code]) {
        key_held[key_code] = ON;
        return ON;
    }

    if (key_held[key_code] && !key[key_code]) {
        key_held[key_code] = OFF;
        return OFF;
    }

    return OFF;
}


FLAG is_key_held(char key_code)
{
    init_keys();
    
    if (key[key_code]) {
        key_held[key_code] = ON;
        return ON;
    }

    key_held[key_code] = OFF;

    return OFF;
}
