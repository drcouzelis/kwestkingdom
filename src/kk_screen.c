#include <stdio.h>

#include "al_screen.h"
#include "kk_screen.h"




#define KK_DEFAULT_COLOR_DEPTH 8




// The canvas is the area inside the screen that
// the game is drawn on.
static BITMAP *kk_canvas = NULL;

// The scale is used to know how big to multiply the canvas.
static int kk_scale = 1;




bool kk_select_best_screen();
bool kk_set_scale();




void kk_set_canvas_size(int width, int height)
{
  if (kk_canvas) {
    destroy_bitmap(kk_canvas);
  }
  
  kk_canvas = create_bitmap(width, height);
  clear_to_color(kk_canvas, makecol(0, 0, 0)); // Black
  kk_set_scale();
}




bool kk_init_screen(int width, int height, bool fullscreen)
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
      fprintf(stderr, "Failed to set graphics mode to fullscreen %dx%d. \n", width, height);
      return false;
    }
    
  } else {
  
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0)) {
      fprintf(stderr, "Failed to set graphics mode to windowed %dx%d. \n", width, height);
      return false;
    }
    
  }
  
  if (!kk_select_best_screen()) {
    return false;
  }
  
  kk_set_scale();
  
  return true;
}




void kk_free_screen()
{
  if (kk_canvas) {
    destroy_bitmap(kk_canvas);
    kk_canvas = NULL;
  }
  shutdown_screen_updating();
}




void kk_set_colors(PALETTE *palette)
{
  set_palette(*palette);
}




inline int kk_canvas_width()
{
  if (kk_canvas) {
    return kk_canvas->w;
  }
  return 0;
}




inline int kk_canvas_height()
{
  if (kk_canvas) {
    return kk_canvas->h;
  }
  return 0;
}




bool kk_update_screen()
{
  if (!screen) {
    fprintf(stderr, "Failed to find a screen to show. \n");
    return false;
  }

  if (!kk_canvas) {
    fprintf(stderr, "Failed to find a window to draw. \n");
    return false;
  }
  
  // Scale the window onto the screen.
  stretch_blit(
    kk_canvas,
    get_buffer(),
    0,
    0,
    kk_canvas_width(),
    kk_canvas_height(),
    (SCREEN_W / 2) - (kk_canvas_width() / 2 * kk_scale),
    (SCREEN_H / 2) - (kk_canvas_height() / 2 * kk_scale),
    kk_canvas_width() * kk_scale,
    kk_canvas_height() * kk_scale
  );
  
  update_screen();

  return true;
}
 



inline BITMAP * kk_get_canvas()
{
  return kk_canvas;
}




inline int kk_screen_width()
{
  if (screen) {
    return screen->w;
  }
  return 0;
}




inline int kk_screen_height()
{
  if (screen) {
    return screen->h;
  }
  return 0;
}




void kk_get_screen_update_method(char *empty_string)
{
  int method;
  
  method = get_update_method();
  
  if (method == UPDATE_TRIPLE_BUFFER) {
    strcpy(empty_string, "Triple Buffering");
  } else if (method == UPDATE_PAGE_FLIP) {
    strcpy(empty_string, "Page Flipping");
  } else if (method == UPDATE_SYSTEM_BUFFER) {
    strcpy(empty_string, "System Buffering");
  } else if (method == UPDATE_DOUBLE_BUFFER) {
    strcpy(empty_string, "Double Buffering");
  } else {
    strcpy(empty_string, "Unknown");
  }
}




/**
 * Internal functions
 */




bool kk_select_best_screen()
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
    fprintf(stderr, "Failed to initialize screen updating. \n");
    return false;
  }
  
  return true;
}




bool kk_set_scale()
{
  int x_scale;
  int y_scale;
  
  if (screen && kk_canvas) {
  
    x_scale = screen->w / kk_canvas->w;
    y_scale = screen->h / kk_canvas->h;
    
    if (x_scale < y_scale) {
      kk_scale = x_scale;
    } else {
      kk_scale = y_scale;
    }
    
    return true;
  }
  
  return false;
}


