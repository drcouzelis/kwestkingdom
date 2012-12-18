#include <allegro.h>
#include <stdio.h>

#include "al_screen.h"
#include "KwestKingdom.h"
#include "screen.h"


#define DEFAULT_COLOR_DEPTH 8


/* The window is the area inside the screen that the game is drawn on */
static BITMAP *window = NULL;

/* The scale is used to know how big to multiply the window */
static int scale = DEFAULT_SCREEN_RATIO;


int select_best_screen()
{
  enable_vsync();
  
  if (initialize_screen_updating(UPDATE_TRIPLE_BUFFER)) {
    // Using triple buffer.
  } else if (initialize_screen_updating(UPDATE_PAGE_FLIP)) {
    // Using page flip.
  } else if (initialize_screen_updating(UPDATE_SYSTEM_BUFFER)) {
    // Using system buffer.
  } else if (initialize_screen_updating(UPDATE_DOUBLE_BUFFER)) {
    // Using double buffer.
  } else {
    printf("Failed to initialize screen updating. \n");
    return 0;
  }
  
  return 1;
}


int set_scale()
{
  int xScale;
  int yScale;

  if (screen && window) {
  
    xScale = screen->w / window->w;
    yScale = screen->h / window->h;
    
    if (xScale < yScale) {
      scale = xScale;
    } else {
      scale = yScale;
    }

    return 1;
  }
  
  return 0;
}


void set_win_size(int width, int height)
{
  if (window) {
    destroy_bitmap(window);
  }
  
  window = create_bitmap(width, height);
  clear_to_color(window, BLACK);
  set_scale();
}


int init_screen(int width, int height, int fullscreen)
{
  int colorDepth;

  if (screen) {
    shutdown_screen_updating();
  }

  // Set the color depth.
  colorDepth = desktop_color_depth();
  if (colorDepth == 0) {
    colorDepth = DEFAULT_COLOR_DEPTH;
  }
  set_color_depth(colorDepth);

  if (width < 0) {
    width = SCREEN_W;
  }

  if (height < 0) {
    height = SCREEN_H;
  }
 
  // Start the screen
  if (fullscreen) {
    
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, width, height, 0, 0)) {
      printf("Failed to set graphics mode to fullscreen %dx%d. \n", width, height);
      return 0;
    }
    
  } else {
  
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0)) {
      printf("Failed to set graphics mode to windowed %dx%d. \n", width, height);
      return 0;
    }

  }
  
  if (select_best_screen() == 0) {
    return 0;
  }

  set_scale();
  
  return 1;
}
 

void free_screen()
{
  if (window) {
    destroy_bitmap(window);
    window = NULL;
  }
  shutdown_screen_updating();
}


int get_win_w()
{
  if (window) {
    return window->w;
  }
  return 0;
}


int get_win_h()
{
  if (window) {
    return window->h;
  }
  return 0;
}


int show_screen()
{
  /*
  int x;
  int y;
  */

  if (screen == NULL) {
    printf("Failed to find a screen to show. \n");
    return 0;
  }

  if (window == NULL) {
    printf("Failed to find a window to draw. \n");
    return 0;
  }

  /*
  x = getTileSize() / 5;
  y = get_win_h() - (getTileSize() / 2);
  
  switch (get_update_method()) {
  case UPDATE_TRIPLE_BUFFER:
    textprintf_ex(get_win(), font, x, y, WHITE, -1, "Triple Buffering");
    break;
  case UPDATE_PAGE_FLIP:
    textprintf_ex(get_win(), font, x, y, WHITE, -1, "Page Flipping");
    break;
  case UPDATE_SYSTEM_BUFFER:
    textprintf_ex(get_win(), font, x, y, WHITE, -1, "System Buffering");
    break;
  case UPDATE_DOUBLE_BUFFER:
    textprintf_ex(get_win(), font, x, y, WHITE, -1, "Double Buffering");
    break;
  }
  */
  
  /* Scale the window onto the screen */
  stretch_blit(
    get_win(),
    get_buffer(),
    0,
    0,
    get_win_w(),
    get_win_h(),
    (SCREEN_W / 2) - (get_win_w() / 2 * scale),
    (SCREEN_H / 2) - (get_win_h() / 2 * scale),
    get_win_w() * scale,
    get_win_h() * scale
  );
  
  update_screen();

  return 0;
}
 

BITMAP *get_win() {
  return window;
}

