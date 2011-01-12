#include "game.h"
#include "engine.h"
#include "memory.h"
#include "mainmenu.h"




enum
{
  ENGINE_INTRO_STATE = 0,
  ENGINE_MAINMENU_STATE,
  ENGINE_GAME_STATE
};




int engine_state = ENGINE_MAINMENU_STATE;




void init_engine()
{
  init_mainmenu();
  show_mainmenu();
}




void stop_engine()
{
  /*destroy_intro(engine->intro);*/
  stop_game();
  stop_mainmenu();
}




void update_engine()
{
  switch (engine_state) {
    
  case ENGINE_INTRO_STATE:
    /*update_intro(engine->intro);*/
    break;
    
  case ENGINE_MAINMENU_STATE:
    update_mainmenu();
    break;
    
  case ENGINE_GAME_STATE:
    update_game();
    break;
    
  }
}




void paint_engine(BITMAP *canvas)
{
  switch (engine_state) {
    
  case ENGINE_INTRO_STATE:
    /*paint_intro(engine->intro, canvas);*/
    break;
    
  case ENGINE_MAINMENU_STATE:
    paint_mainmenu(canvas);
    break;
    
  case ENGINE_GAME_STATE:
    paint_game(canvas);
    break;
    
  }
}




void show_mainmenu()
{
  generate_mainmenu_background();
  engine_state = ENGINE_MAINMENU_STATE;
}




void start_story_game()
{
  init_story_game();
  engine_state = ENGINE_GAME_STATE;
}




void start_endless_game()
{
  printf("Pretending to start endless game. \n");
  init_story_game();
  engine_state = ENGINE_GAME_STATE;
}




void resume_game()
{
  engine_state = ENGINE_GAME_STATE;
}
