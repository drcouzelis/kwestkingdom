#ifndef ENGINE_HEADER
#define ENGINE_HEADER


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


ENGINE *create_engine();
void destroy_engine();

void update_engine(ENGINE *engine);
void paint_engine(ENGINE *engine, BITMAP *canvas);

void show_mainmenu(ENGINE *engine);

void start_story_game(ENGINE *engine);
void start_endless_game(ENGINE *engine);

void resume_game(ENGINE *engine);


#endif
