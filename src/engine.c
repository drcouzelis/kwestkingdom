#include "game.h"
#include "engine.h"
#include "memory.h"
#include "mainmenu.h"




MAINMENU *menu = NULL;
  
GAME *game = NULL;
  



enum
{
  ENGINE_INTRO_STATE = 0,
  ENGINE_MAINMENU_STATE,
  ENGINE_GAME_STATE
};




int engine_state = ENGINE_MAINMENU_STATE;




void init_engine()
{
  menu = create_mainmenu();
  show_mainmenu();
}




void stop_engine()
{
  destroy_game(game);
  game = NULL;
  
  /*destroy_intro(intro);*/
  /*intro = NULL;*/
  
  destroy_mainmenu(menu);
  menu = NULL;
}




void update_engine()
{
  switch (engine_state) {
    
  case ENGINE_INTRO_STATE:
    /*update_intro(intro);*/
    break;
    
  case ENGINE_MAINMENU_STATE:
    update_mainmenu(menu);
    break;
    
  case ENGINE_GAME_STATE:
    update_game(game);
    break;
    
  }
}




void paint_engine(BITMAP *canvas)
{
  switch (engine_state) {
    
  case ENGINE_INTRO_STATE:
    /*paint_intro(intro, canvas);*/
    break;
    
  case ENGINE_MAINMENU_STATE:
    paint_mainmenu(menu, canvas);
    break;
    
  case ENGINE_GAME_STATE:
    paint_game(game, canvas);
    break;
    
  }
}




void show_mainmenu()
{
  reload_mainmenu(menu);
  engine_state = ENGINE_MAINMENU_STATE;
}




void play_story_game()
{
  destroy_game(game);
  game = create_story_game();
  
  engine_state = ENGINE_GAME_STATE;
}




void play_endless_game()
{
  printf("Pretending to start endless game. \n");
  destroy_game(game);
  game = NULL; /*create_story_game();*/
  
  engine_state = ENGINE_GAME_STATE;
}




FLAG can_resume_game()
{
  if (game == NULL) {
    return OFF;
  }
  
  return ON;
}




void resume_game()
{
  engine_state = ENGINE_GAME_STATE;
}
