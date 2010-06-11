#include <allegro.h>
#include <stdbool.h>
#include <stdio.h>

#include "kk_anim.h"
#include "kk_color.h"
#include "kk_input.h"
#include "kk_main.h"
#include "kk_resources.h"
#include "kk_screen.h"
#include "kk_timer.h"




#define KK_TILE_SIZE 20

#define KK_COLS 16
#define KK_ROWS 12

#define KK_CANVAS_WIDTH (KK_COLS * KK_TILE_SIZE)
#define KK_CANVAS_HEIGHT (KK_ROWS * KK_TILE_SIZE)

#define KK_DEFAULT_SCREEN_RATIO 2




inline int kk_tile_size()
{
  return KK_TILE_SIZE;
}




inline int kk_walk_speed()
{
  return 60;
}




static bool kk_quit = false;




inline void kk_quit_game()
{
  kk_quit = true;
}




void kk_init_game()
{
  bool screen_init;
  
  allegro_init();
  kk_init_timer();
  install_keyboard();
  kk_init_resources(); // Load images
  
  screen_init = kk_init_screen(
    KK_CANVAS_WIDTH * KK_DEFAULT_SCREEN_RATIO,
    KK_CANVAS_HEIGHT * KK_DEFAULT_SCREEN_RATIO,
    false // fullscreen
  );
  
  if (!screen_init) {
    exit(0);
  }
  
  kk_set_colors(kk_get_palette());
  kk_set_canvas_size(KK_CANVAS_WIDTH, KK_CANVAS_HEIGHT);
  
  install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
  kk_toggle_sound(); // Turn off sound
}




int main(int argc, char **argv)
{
  int time;
  char method[KK_SCREEN_UPDATE_STR_LEN];
  KK_KEY *quit_key;
  
  KK_ANIM *hero;
  
  kk_init_game();
  
  quit_key = kk_key_create(KEY_ESC, false);
  
  hero = kk_anim_create(6, true);
  kk_anim_add_frame(hero, kk_get_image(KK_IMG_HERO_STAND_1));
  kk_anim_add_frame(hero, kk_get_image(KK_IMG_HERO_STAND_2));
  kk_anim_add_frame(hero, kk_get_image(KK_IMG_HERO_STAND_3));
  kk_anim_add_frame(hero, kk_get_image(KK_IMG_HERO_STAND_2));
  
  // Reset the timers just before the game begins.
  kk_reset_timer();
  
  while (!kk_quit) {
    
    while (kk_ticks() == 0) {
      rest(1);
    }
    
    while (kk_ticks() > 0) {
      
      time = kk_ticks();
      
      if (kk_key_is_pressed(quit_key)) {
        kk_quit_game();
      }
      
      //
      // UPDATE
      //
      //[game update];
      kk_anim_animate(hero);
      
      kk_decrease_timer();
      
      if (time <= kk_ticks()) {
        break;
      }
      
    }
    
    //
    // DRAW
    //
    clear_to_color(kk_get_canvas(), KK_RED); // TEMP
    //[game draw: getWindow()];
    kk_anim_draw(hero, kk_get_canvas(), kk_tile_size() * 4, kk_tile_size() * 4);
    
    // Show FPS
    textprintf_ex(
      kk_get_canvas(),
      font,
      10,
      10,
      KK_WHITE,
      -1,
      "FPS %d",
      kk_get_fps()
    );
    
    // Show the method of screen updating.
    kk_get_screen_update_method(method);
    
    textprintf_ex(
      kk_get_canvas(),
      font,
      kk_tile_size() / 5, // x
      kk_canvas_height() - (kk_tile_size() / 2), // y
      KK_WHITE,
      -1,
      method
    );
    
    // Show all of the new screen changes
    kk_update_screen();
    
    // This is for counting FPS
    kk_frame_complete();
  }
  
  //
  // Cleanup
  //
  //[game free];
  kk_anim_destroy(hero, false);
  kk_free_screen();
  kk_free_resources();
  
  return 0;
}
END_OF_MAIN()
