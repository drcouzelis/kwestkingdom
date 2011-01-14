#ifndef ENGINE_HEADER
#define ENGINE_HEADER


#include "utilities.h"


typedef struct ENGINE ENGINE;
struct GAME;
struct MAINMENU;


void init_engine();
void stop_engine();

void update_engine();
void paint_engine(BITMAP *canvas);

void show_mainmenu();
void play_story_game();
void play_endless_game();

FLAG can_resume_game();
void resume_game();

struct GAME *grab_game();


#endif
