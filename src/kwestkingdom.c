#include <allegro.h>
#include <stdio.h>

#include "colors.h"
#include "engine.h"
#include "game.h"
#include "input.h"
#include "memory.h"
#include "resources.h"
#include "room.h"
#include "screen.h"
#include "sound.h"
#include "timer.h"
#include "utilities.h"
#include "kwestkingdom.h"




/**
 * Private
 */




#define CANVAS_WIDTH (COLS * grab_tile_size())
#define CANVAS_HEIGHT (ROWS * grab_tile_size())

#define DEFAULT_SCREEN_RATIO 2




static FLAG quitting = OFF;




FLAG init_kwestkingdom()
{
  FLAG screen_init;

  allegro_init();
  init_timer();
  install_keyboard();
  init_input();
  
  if (!init_resources()) { /* Load images and sounds */
    return OFF;
  }

  screen_init = init_screen(
    CANVAS_WIDTH * DEFAULT_SCREEN_RATIO,
    CANVAS_HEIGHT * DEFAULT_SCREEN_RATIO,
    OFF /* fullscreen on or off */
  );

  if (!screen_init) {
    return OFF;
  }

  change_colors(grab_color_palette());
  change_canvas_size(CANVAS_WIDTH, CANVAS_HEIGHT);

  install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
  toggle_sound(); /* Turn off sound */
  
  return ON;
}




/**
 * Public
 */




int grab_walk_speed()
{
  return 60;
}




void quit_kwestkingdom()
{
  quitting = ON;
}




int main(int argc, char *argv[])
{
  int time;
  char method[SCREEN_UPDATE_STR_LEN];
  
  if (argc > 1) {
    if (strstr(argv[1], "help")) {
      printf("Type \"kwestkingdom\" to play!\n");
      exit(0);
    }
  }

  if (!init_kwestkingdom()) {
    return 1;
  }

  init_engine();

  /**
   * Reset the timers just before the game begins.
   */
  reset_timer();

  /**
   * BEGIN MAIN LOOP
   */
  while (!quitting) {

    while (get_ticks() == 0) {
      rest(1);
    }

    while (get_ticks() > 0) {

      time = get_ticks();

      /**
       * UPDATE
       */
      update_engine();

      decrease_timer();

      if (time <= get_ticks()) {
        break;
      }

    }

    /**
     * DRAW
     */
    paint_engine(grab_canvas());

    /**
     * Show FPS
     */
    textprintf_ex(
      grab_canvas(),
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
    find_screen_update_method(method);

    textprintf_ex(
      grab_canvas(),
      font,
      grab_tile_size() / 5, /* x */
      grab_canvas_height() - (grab_tile_size() / 2), /* y */
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
   * END MAIN LOOP
   */

  /**
   * Cleanup
   */
  stop_engine();
  stop_screen();
  stop_resources();
  
  check_memory();
  
  return 0;
}
END_OF_MAIN()
