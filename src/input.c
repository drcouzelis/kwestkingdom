#include <allegro.h>
#include "input.h"




/**
 * Private
 */




static char key_held[KEY_MAX];




/**
 * Public
 */




void init_input()
{
  unsigned int i;
  
  for (i = 0; i < KEY_MAX; i++) {
    key_held[i] = OFF;
  }
}




FLAG is_key_pressed(char code)
{
  unsigned int i = code;
  
  if (!key_held[i] && key[i]) {
    key_held[i] = ON;
    return ON;
  }
  
  if (key_held[i] && !key[i]) {
    key_held[i] = OFF;
    return OFF;
  }
  
  return OFF;
}




FLAG is_key_held(char code)
{
  unsigned int i = code;
  
  if (key[i]) {
    key_held[i] = ON;
    return ON;
  }

  key_held[i] = OFF;

  return OFF;
}
