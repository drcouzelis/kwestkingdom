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




ENGINE * create_engine()
{
  ENGINE *engine;
  
  engine = alloc_memory(sizeof(ENGINE));
  
  /*engine->intro = NULL;*/
  engine->game = NULL;
  engine->menu = create_mainmenu();
  
  show_mainmenu(engine);
  
  return engine;
}




void destroy_engine(ENGINE *engine)
{
  if (engine == NULL) {
    return;
  }
  
  /*destroy_intro(engine->intro);*/
  destroy_game(engine->game);
  destroy_mainmenu(engine->menu);
  
  free_memory(engine);
}




void update_engine(ENGINE *engine)
{
  switch (engine->state) {
    
  case ENGINE_INTRO_STATE:
    /*update_intro(engine->intro);*/
    break;
    
  case ENGINE_MAINMENU_STATE:
    update_mainmenu(engine->menu, engine);
    break;
    
  case ENGINE_GAME_STATE:
    update_game(engine->game, engine);
    break;
    
  }
}




void paint_engine(ENGINE *engine, BITMAP *canvas)
{
  switch (engine->state) {
    
  case ENGINE_INTRO_STATE:
    /*paint_intro(engine->intro, canvas);*/
    break;
    
  case ENGINE_MAINMENU_STATE:
    paint_mainmenu(engine->menu, canvas);
    break;
    
  case ENGINE_GAME_STATE:
    paint_game(engine->game, canvas);
    break;
    
  }
}




void show_mainmenu(ENGINE *engine)
{
  generate_mainmenu_background(engine->menu);
  engine->state = ENGINE_MAINMENU_STATE;
}




void start_story_game(ENGINE *engine)
{
  destroy_game(engine->game);
  engine->game = create_story_game();
  
  engine->state = ENGINE_GAME_STATE;
}




void start_endless_game(ENGINE *engine)
{
  printf("Pretending to start endless game. \n");
  destroy_game(engine->game);
  engine->game = NULL; /*create_story_game();*/
  
  engine->state = ENGINE_GAME_STATE;
}




void resume_game(ENGINE *engine)
{
  engine->state = ENGINE_GAME_STATE;
}
