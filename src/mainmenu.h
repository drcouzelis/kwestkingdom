#ifndef MAINMENU_HEADER
#define MAINMENU_HEADER


#include <allegro.h>

#include "utilities.h"


typedef struct MAINMENU MAINMENU;
struct ANIM;
struct ENGINE;


struct MAINMENU
{
  /**
   * The title screen image
   */
  struct ANIM *title_anim;
  
  /**
   * The selection icon
   */
  struct ANIM *pointer_anim;
  
  /**
   * The title screen background
   */
  BITMAP *title_background;
  
  /**
   * Whether or not there is an active game
   */
  FLAG game_is_active;
  
  /**
   * Which line the menu pointer is on
   */
  int selection;
  
  int state;
};


MAINMENU *create_mainmenu();
void destroy_mainmenu(MAINMENU *menu);

void update_mainmenu(MAINMENU *menu, ENGINE *engine);
void paint_mainmenu(MAINMENU *menu, BITMAP *canvas);

void generate_mainmenu_background(MAINMENU *menu);

#endif
