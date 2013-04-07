#ifndef KEY_INPUT_HEADER
#define KEY_INPUT_HEADER

#include "utilities.h"

#ifdef __cplusplus
  extern "C" {
#endif


typedef struct
{
  int key_code;
  int delay; // Number of ticks to wait until the action for this key is performed again
  int timer; // Update every tick while the key is pressed
  FLAG released;
} KEY_INPUT;


void init_key_input(KEY_INPUT *key_input, int key_code, int delay);

FLAG is_key_pressed(KEY_INPUT *input);


#ifdef __cplusplus
  }
#endif

#endif
