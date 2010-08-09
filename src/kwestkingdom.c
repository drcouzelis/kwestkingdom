#include <allegro.h>
#include <stdio.h>

#include <allegro.h>
#include "kk_colors.h"
#include "kk_game.h"
/*#include "kk_input.h"*/
#include "kk_screen.h"
#include "kk_timer.h"
#include "kk_utilities.h"
#include "kwestkingdom.h"


#define TILE_SIZE 20

#define COLS 16
#define ROWS 12

#define CANVAS_WIDTH (COLS * TILE_SIZE)
#define CANVAS_HEIGHT (ROWS * TILE_SIZE)

#define DEFAULT_SCREEN_RATIO 2


int get_tile_size()
{
  return TILE_SIZE;
}


int get_walk_speed()
{
  return 60;
}


static FLAG quitting = OFF;


void quit_kwestkingdom()
{
  quitting = ON;
}


void init_kwestkingdom()
{
  FLAG screen_init;
  
  allegro_init();
  init_timer();
  install_keyboard();
  /*init_resources();*/ /* Load images */
  
  screen_init = init_screen(
    CANVAS_WIDTH * DEFAULT_SCREEN_RATIO,
    CANVAS_HEIGHT * DEFAULT_SCREEN_RATIO,
    OFF /* fullscreen */
  );
  
  if (!screen_init) {
    exit(0);
  }
  
  /*set_colors(get_palette());*/
  set_canvas_size(CANVAS_WIDTH, CANVAS_HEIGHT);
  
  install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
  /*toggle_sound();*/ /* Turn off sound */
}


int main(int argc, char *argv[])
{
  GAME *game;
  
  int time;
  char method[SCREEN_UPDATE_STR_LEN];
  
  if (argc > 1) {
    if (strstr(argv[1], "help")) {
      printf("Type \"kwestkingdom\" to play!\n");
    }
  }
  
  init_kwestkingdom();
  
  game = create_game();
  
  /**
   * Reset the timers just before the game begins.
   */
  reset_timer();
  
  while (!quitting) {
    
    while (get_ticks() == 0) {
      rest(1);
    }
    
    while (get_ticks() > 0) {
      
      time = get_ticks();
      
      /*if (key_is_pressed(quit_key)) {*/
      if (key[KEY_ESC]) {
        quit_kwestkingdom();
      }
      
      /**
       * UPDATE
       */
      update_game(game);
      
      decrease_timer();
      
      if (time <= get_ticks()) {
        break;
      }
      
    }
    
    /**
     * DRAW
     */
    clear_to_color(get_canvas(), RED); /* TEMP */
    paint_game(game, get_canvas());
    
    /*
     * Show FPS
     */
    textprintf_ex(
      get_canvas(),
      font,
      10,
      10,
      WHITE,
      -1,
      "FPS %d",
      get_fps()
    );
    
    /**
     * Show the method of screen updating.
     */
    get_screen_update_method(method);
    
    textprintf_ex(
      get_canvas(),
      font,
      get_tile_size() / 5, /* x */
      canvas_height() - (get_tile_size() / 2), /* y */
      WHITE,
      -1,
      method
    );
    
    /**
     * Show all of the new screen changes
     */
    refresh_screen();
    
    mark_frame_complete();
  }
  
  /**
   * Cleanup
   */
  destroy_game(game);
  stop_screen();
  /*stop_resources();*/
  
  return 0;
}
END_OF_MAIN()
