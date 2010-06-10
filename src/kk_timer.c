#include <allegro.h>

#include "kk_timer.h"




static volatile int kk_timer = 0;
static volatile int kk_fps_timer = 0;




/**
 * To keep the game running at the correct frames per second
 */
void KK_increase_timer()
{
  kk_timer++;
} END_OF_FUNCTION(KK_increase_timer);




/**
 * To display the current frames per second
 */
void KK_increase_fps_ticker()
{
  kk_fps_timer++;
}
END_OF_FUNCTION(KK_increase_fps_ticker)




inline int KK_ticks()
{
  return kk_timer;
}




inline void KK_decrease_timer()
{
  kk_timer--;
}




static int kk_fps = 0;
static int kk_frames_done = 0;
static int kk_prev_time = 0;




inline int KK_get_fps()
{
  // If a second has passed since we last measured the frame rate...
  if (kk_fps_timer - kk_prev_time >= 10) {
    
    // fps now holds the the number of frames done in the last second.
    kk_fps = kk_frames_done;
    
    // Reset for the next second
    kk_frames_done = 0;
    
    kk_prev_time = kk_fps_timer;
  }
  
  return kk_fps;
}




inline void KK_update_fps()
{
  kk_frames_done++;
}




void KK_init_timer()
{
  install_timer();
  
  LOCK_VARIABLE(kk_timer);
  LOCK_FUNCTION(KK_increase_timer);
  install_int_ex(KK_increase_timer, BPS_TO_TIMER(KK_GAME_TICKER));
  
  LOCK_VARIABLE(kk_fps_timer);
  LOCK_FUNCTION(KK_increase_fps_ticker);
  install_int_ex(KK_increase_fps_ticker, BPS_TO_TIMER(10));
  
  KK_reset_timer();
}




void KK_reset_timer()
{
  kk_timer = 0;
  kk_fps_timer = 0;
}

