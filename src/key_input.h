#ifndef KEY_INPUT_HEADER
#define KEY_INPUT_HEADER

#include "utilities.h"

#ifdef __cplusplus
  extern "C" {
#endif


/**
 * See the Allegro documentation for a list of key codes.
 *
 * https://www.allegro.cc/manual/4/api/keyboard-routines/key
 */


/**
 * Returns true if the key has been pressed since
 * the last time this function was called.
 */
FLAG is_key_pressed(char key_code);

/**
 * Returns true if the key is being held down.
 */
FLAG is_key_held(char key_code);


#ifdef __cplusplus
  }
#endif

#endif
