#ifndef KEY_INPUT_HEADER
#define KEY_INPUT_HEADER

#include "utilities.h"

#ifdef __cplusplus
  extern "C" {
#endif


/**
 * See the Allegro documentation for a list of key codes.
 *
 * http://www.allegro.cc/manual/5/keyboard.html
 */


/**
 * Returns true if the key has been pressed since
 * the last time this function was called.
 */
int is_key_pressed(int key);

/**
 * Returns true if the key is being held down.
 */
int is_key_held(int key);


#ifdef __cplusplus
  }
#endif

#endif
