#include <allegro5/allegro.h>
#include <stdio.h>

#include "key_input.h"


void init_key_input(KEY_INPUT *key_input, int key_code, int delay)
{
  key_input->key_code = key_code;
  key_input->delay = delay;
  key_input->released = ON;
  key_input->timer = 0;
}


FLAG is_key_pressed(KEY_INPUT *key_input)
{
  FLAG ret = OFF;
  
  if (key_input->delay == 0 && key[key_input->key_code]) {
    return ON;
  }
  
  if (key[key_input->key_code]) {
    if (key_input->released) {
      
      ret = ON;
      key_input->timer = 0;
      
    } else {
      key_input->timer++;
    }
    
    key_input->released = OFF;
    
    if (key_input->timer >= key_input->delay) {
      key_input->released = ON;
    }
    
  } else {
    key_input->released = ON;
  }
  
  return ret;
}

