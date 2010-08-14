#ifndef INPUT_HEADER
#define INPUT_HEADER


#include "utilities.h"


/**
 * See the Allegro documentation for a list of key codes.
 *
 * http://www.allegro.cc/manual/api/keyboard-routines/key
 */


void init_input();

/**
 * Returns true if the key has been pressed since
 * the last time this function was called.
 */
FLAG is_key_pressed(char code);

/**
 * Returns true if the key is being held down.
 */
FLAG is_key_held(char code);


#endif
