#ifndef GAME_HEADER
#define GAME_HEADER


#include <allegro.h>

#include "utilities.h"


void init_story_game();
void init_endless_game();
void stop_game();

FLAG is_game_over();
FLAG is_game_won();

void update_game();
void paint_game(BITMAP *canvas);

FLAG can_resume_game();


#endif
