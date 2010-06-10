#include <allegro.h>

#include "kk_kwestkingdom.h"
#include "kk_screen.h"
#include "kk_timer.h"
#include "kk_utilities.h"




int KK_tile_size()
{
  return KK_TILE_SIZE;
}




int KK_walk_speed()
{
  return 60;
}




static FLAG kk_quit = OFF;




void KK_quit_game()
{
  kk_quit = ON;
}




void KK_init_game()
{
  FLAG screen_init;
  
  allegro_init();
  
  KK_init_timer();
  
  install_keyboard();
  
  //initializeResources();

  screen_init = KK_init_screen(
    KK_WINDOW_WIDTH * KK_DEFAULT_SCREEN_RATIO,
    KK_WINDOW_HEIGHT * KK_DEFAULT_SCREEN_RATIO,
    OFF
  );
  
  if (!screen_init) {
    exit(0);
  }

  //setPalette();
  KK_set_window_size(KK_WINDOW_WIDTH, KK_WINDOW_HEIGHT);
  
  install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
  //toggleSound(); // Turn off sound

}




int main(int argc, char **argv)
{
  int time;
  
  KK_init_game();
  
  // Reset the timers just before the game begins.
  KK_reset_timer();
  
  //printf("Staring loop... \n");
  
  while (!kk_quit) {
    
    while (KK_ticks() == 0) {
      rest(1);
    }
    
    //printf("Found some ticks... \n");
    
    while (KK_ticks() > 0) {
      
      time = KK_ticks();
      
      //[game update];
      
      KK_decrease_timer();
      
      if (time <= KK_ticks()) {
        break;
      }
      
    }
    
    //printf("Draw screen... \n");
    
    //[game draw: getWindow()];
    clear_to_color(KK_get_window(), makecol(0, 0, 0));
    textprintf_ex(KK_get_window(), font, 10, 10, makecol(255, 255, 255), -1, "FPS %d", KK_get_fps());
    
    KK_refresh_screen();
    
    KK_update_fps();
  }
  
  //[game free];
  
  KK_free_screen();
  
  //destroyResources();
  
  return 0;
}
END_OF_MAIN()
