#include <allegro.h>
#include <malloc.h>

#include "kk_input.h"




struct KK_KEY
{
  int keycode;
  bool repeat;
  bool released;
};




KK_KEY * kk_key_create(int keycode, bool repeat)
{
  KK_KEY *k;
  
  k = malloc(sizeof(*key));
  
  if (k) {
    k->keycode = keycode;
    k->repeat = repeat;
    k->released = true;
  }
  
  return k;
}




void kk_key_destroy(KK_KEY *k)
{
  free(k);
}




bool kk_key_is_pressed(KK_KEY *k)
{
  if (k->repeat && key[k->keycode]) {
    return true;
  }
  
  if (key[k->keycode] && k->released) {
    // The player has pressed a non-repeating key
    // for the first time
    k->released = false;
    return true;
  }
  
  if (!key[k->keycode]) {
    // The player released the key
    k->released = true;
  }
  
  return false;
}
