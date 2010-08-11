#ifndef INPUT_HEADER
#define INPUT_HEADER


#include <allegro.h>
#include "utilities.h"


/**
 * Returns true if the key has been pressed since
 * the last time this function was called.
 */
FLAG is_key_pressed(char keycode);

/**
 * Returns true if the key is being held down.
 */
FLAG is_key_held(char keycode);


#endif
