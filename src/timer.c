#include <allegro.h>
#include "timer.h"


static volatile int timer = 0;
static volatile int fps_timer = 0;


/**
 * To keep the game running at the correct frames per second
 */
void increase_timer()
{
  timer++;
} END_OF_FUNCTION(increase_timer)


/**
 * To display the current frames per second
 */
void increase_fps_ticker()
{
  fps_timer++;
}
END_OF_FUNCTION(increase_fps_ticker)


int get_ticks()
{
  return timer;
}


void decrease_timer()
{
  timer--;
}


static int fps = 0;
static int frames_done = 0;
static int prev_time = 0;


int get_fps()
{
  /* If a second has passed since we last measured the frame rate... */
  if (fps_timer - prev_time >= 10) {
    
    /* fps now holds the the number of frames done in the last second. */
    fps = frames_done;
    
    /* Reset for the next second */
    frames_done = 0;
    
    prev_time = fps_timer;
  }
  
  return fps;
}


void mark_frame_complete()
{
  frames_done++;
}


void init_timer()
{
  install_timer();
  
  LOCK_VARIABLE(timer);
  LOCK_FUNCTION(increase_timer);
  install_int_ex(increase_timer, BPS_TO_TIMER(GAME_TICKER));
  
  LOCK_VARIABLE(fps_timer);
  LOCK_FUNCTION(increase_fps_ticker);
  install_int_ex(increase_fps_ticker, BPS_TO_TIMER(10));
  
  reset_timer();
}


void reset_timer()
{
  timer = 0;
  fps_timer = 0;
}
