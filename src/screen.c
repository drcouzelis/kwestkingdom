#include <stdio.h>
#include "al_screen.h"
#include "screen.h"




#define DEFAULT_COLOR_DEPTH 8




/**
 * The canvas is the area inside the screen that
 * the game is drawn on.
 */
static BITMAP *canvas = NULL;

/**
 * The scale is used to know how big to multiply the canvas.
 */
static int scale = 1;

FLAG select_best_screen();
FLAG update_scale();




void set_canvas_size(int width, int height)
{
  if (canvas) {
    destroy_bitmap(canvas);
  }
  
  canvas = create_bitmap(width, height);
  clear_to_color(canvas, makecol(0, 0, 0)); /* Black */
  update_scale();
}




FLAG init_screen(int width, int height, FLAG fullscreen)
{
  int colordepth;
  
  if (screen) {
    shutdown_screen_updating();
  }
  
  /* Set the color depth */
  colordepth = desktop_color_depth();
  
  if (colordepth == 0) {
    colordepth = DEFAULT_COLOR_DEPTH;
  }
  
  set_color_depth(colordepth);
  
  if (width < 0) {
    width = SCREEN_W;
  }
  
  if (height < 0) {
    height = SCREEN_H;
  }
  
  /* Start the screen */
  if (fullscreen) {
    
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, width, height, 0, 0)) {
      fprintf(stderr, "Failed to set graphics mode to fullscreen %dx%d.\n", width, height);
      return OFF;
    }
    
  } else {
  
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0)) {
      fprintf(stderr, "Failed to set graphics mode to windowed %dx%d.\n", width, height);
      return OFF;
    }
    
  }
  
  if (!select_best_screen()) {
    return OFF;
  }
  
  update_scale();
  
  return ON;
}




void stop_screen()
{
  if (canvas) {
    destroy_bitmap(canvas);
    canvas = NULL;
  }
  shutdown_screen_updating();
}




void set_colors(PALETTE *palette)
{
  set_palette(*palette);
}




int canvas_width()
{
  if (canvas) {
    return canvas->w;
  }
  return 0;
}




int canvas_height()
{
  if (canvas) {
    return canvas->h;
  }
  return 0;
}




void refresh_screen()
{
  if (!screen) {
    fprintf(stderr, "Failed to find a screen to show.\n");
    return;
  }

  if (!canvas) {
    fprintf(stderr, "Failed to find a canvas to draw.\n");
    return;
  }
  
  /**
   * Scale the window onto the screen.
   */
  stretch_blit(
    canvas,
    get_buffer(),
    0,
    0,
    canvas_width(),
    canvas_height(),
    (SCREEN_W / 2) - (canvas_width() / 2 * scale),
    (SCREEN_H / 2) - (canvas_height() / 2 * scale),
    canvas_width() * scale,
    canvas_height() * scale
  );
  
  update_screen();
}




BITMAP * get_canvas()
{
  return canvas;
}




int screen_width()
{
  if (screen) {
    return screen->w;
  }
  return 0;
}




int screen_height()
{
  if (screen) {
    return screen->h;
  }
  return 0;
}




void get_screen_update_method(char *empty_string)
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




FLAG select_best_screen()
{
  enable_vsync();
  
  if (initialize_screen_updating(UPDATE_TRIPLE_BUFFER)) {
    /* Using triple buffer */
  } else if (initialize_screen_updating(UPDATE_PAGE_FLIP)) {
    /* Using page flip */
  } else if (initialize_screen_updating(UPDATE_SYSTEM_BUFFER)) {
    /* Using system buffer */
  } else if (initialize_screen_updating(UPDATE_DOUBLE_BUFFER)) {
    /* Using double buffer */
  } else {
    fprintf(stderr, "Failed to initialize screen updating.\n");
    return OFF;
  }
  
  return ON;
}




FLAG update_scale()
{
  int x_scale;
  int y_scale;
  
  if (screen && canvas) {
  
    x_scale = screen->w / canvas->w;
    y_scale = screen->h / canvas->h;
    
    if (x_scale < y_scale) {
      scale = x_scale;
    } else {
      scale = y_scale;
    }
    
    return ON;
  }
  
  return OFF;
}
