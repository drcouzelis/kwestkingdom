#include <stdio.h>

#include <allegro5/allegro.h>

#include "KwestKingdom.h"
#include "resources.h"
#include "screen.h"


static IMAGE *screen = NULL;


FLAG init_screen(int width, int height, int fullscreen)
{
  if (screen) {
    destroy_bitmap(screen);
  }

  // Start the screen
  if (fullscreen) {
    
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, width, height, 0, 0)) {
      printf("Failed to set graphics mode to fullscreen %dx%d. \n", width, height);
      return OFF;
    }
    
  } else {
  
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0)) {
      printf("Failed to set graphics mode to windowed %dx%d. \n", width, height);
      return OFF;
    }

  }
  
  return ON;
}
 

void free_screen()
{
  if (screen) {
    destroy_bitmap(screen);
    screen = NULL;
  }
}


FLAG show_screen()
{
  /* Scale the window onto the screen */
  stretch_blit(
    get_buffer(),
    0,
    0,
    screen->w,
    screen->h,
    (SCREEN_W / 2) - (screen->w / 2 * screen_scale),
    (SCREEN_H / 2) - (screen->h / 2 * screen_scale),
    screen->w * screen_scale,
    screen->h * screen_scale
  );
  
  update_screen();

  return ON;
}

