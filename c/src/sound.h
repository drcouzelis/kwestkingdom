#ifndef SOUND_HEADER
#define SOUND_HEADER


#include <allegro.h>
#include "utilities.h"


void play_sound(SAMPLE *sound);

void toggle_sound();
FLAG is_sound_enabled();


#endif
