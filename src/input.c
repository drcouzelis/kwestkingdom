#include "input.h"




FLAG is_key_pressed(char keycode)
{
  /**
   * Check every key that made it into the key buffer since we last checked it.
   */
  while (keypressed())
  {
    /**
     * Check what the key code is for the current key we're
     * reading from the key buffer.
     */
    if (readkey() >> 8 == keycode) {
      return ON;
    }
  }

  return OFF;
}




FLAG is_key_held(char keycode)
{
  /*
  if (key[keycode]) {
    key_released[keycode] = OFF;
    return ON;
  }

  key_released[keycode] = ON;

  return OFF;
  */
  return key[keycode];
}
