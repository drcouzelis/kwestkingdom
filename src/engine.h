#ifndef ENGINE_HEADER
#define ENGINE_HEADER


#include "utilities.h"


typedef struct ENGINE ENGINE;
struct GAME;
/*struct INTRO;*/
struct MAINMENU;


struct ENGINE
{
  /*struct INTRO *intro;*/
  
  struct MAINMENU *menu;
  
  struct GAME *game;
  
  int state;
};


void init_engine();
void stop_engine();

void update_engine();
void paint_engine(BITMAP *canvas);

void show_mainmenu();
void start_story_game();
void start_endless_game();
void resume_game();


#endif
