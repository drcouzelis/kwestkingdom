#include <stdio.h>

#include "kk_screen.h"




#define KK_DEFAULT_COLOR_DEPTH 8




// The window is the area inside the screen that
// the game is drawn on.
static BITMAP *kk_window = NULL;

// The scale is used to know how big to multiply the window.
static int kk_scale = KK_DEFAULT_SCREEN_RATIO;


FLAG KK_select_best_screen()
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
    return OFF;
  }
  
  return ON;
}


FLAG KK_set_scale()
{
  int x_scale;
  int y_scale;

  if (screen && kk_window) {
  
    x_scale = screen->w / kk_window->w;
    y_scale = screen->h / kk_window->h;
    
    if (x_scale < y_scale) {
      kk_scale = x_scale;
    } else {
      kk_scale = y_scale;
    }

    return ON;
  }
  
  return OFF;
}


void KK_set_window_size(int width, int height)
{
  if (kk_window) {
    destroy_bitmap(kk_window);
  }
  
  kk_window = create_bitmap(width, height);
  clear_to_color(kk_window, makecol(0, 0, 0));
  KK_set_scale();
}


FLAG KK_init_screen(int width, int height, FLAG fullscreen)
{
  int colordepth;

  if (screen) {
    shutdown_screen_updating();
  }

  // Set the color depth.
  colordepth = desktop_color_depth();
  
  if (colordepth == 0) {
    colordepth = KK_DEFAULT_COLOR_DEPTH;
  }
  
  set_color_depth(colordepth);

  if (width < 0) {
    width = SCREEN_W;
  }

  if (height < 0) {
    height = SCREEN_H;
  }
 
  // Start the screen.
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
  
  if (!KK_select_best_screen()) {
    return OFF;
  }

  KK_set_scale();
  
  return ON;
}
 



void KK_free_screen()
{
  if (kk_window) {
    destroy_bitmap(kk_window);
    kk_window = NULL;
  }
  shutdown_screen_updating();
}


int KK_window_width()
{
  if (kk_window) {
    return kk_window->w;
  }
  return 0;
}




int KK_window_height()
{
  if (kk_window) {
    return kk_window->h;
  }
  return 0;
}




FLAG KK_refresh_screen()
{
  int x;
  int y;
  int color;

  if (!screen) {
    printf("Failed to find a screen to show. \n");
    return OFF;
  }

  if (!kk_window) {
    printf("Failed to find a window to draw. \n");
    return OFF;
  }

  x = KK_tile_size() / 5;
  y = KK_window_height() - (KK_tile_size() / 2);
  
  color = makecol(255, 255, 255);
  
  switch (get_update_method()) {
  case UPDATE_TRIPLE_BUFFER:
    textprintf_ex(kk_window, font, x, y, color, -1, "Triple Buffering");
    break;
  case UPDATE_PAGE_FLIP:
    textprintf_ex(kk_window, font, x, y, color, -1, "Page Flipping");
    break;
  case UPDATE_SYSTEM_BUFFER:
    textprintf_ex(kk_window, font, x, y, color, -1, "System Buffering");
    break;
  case UPDATE_DOUBLE_BUFFER:
    textprintf_ex(kk_window, font, x, y, color, -1, "Double Buffering");
    break;
  }
  
  // Scale the window onto the screen.
  stretch_blit(
    kk_window,
    get_buffer(),
    0,
    0,
    KK_window_width(),
    KK_window_height(),
    (SCREEN_W / 2) - (KK_window_width() / 2 * kk_scale),
    (SCREEN_H / 2) - (KK_window_height() / 2 * kk_scale),
    KK_window_width() * kk_scale,
    KK_window_height() * kk_scale
  );
  
  update_screen();

  return ON;
}
 



BITMAP * KK_get_window()
{
  return kk_window;
}

