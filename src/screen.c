#include <stdio.h>

#include "al_screen.h"
#include "screen.h"




/**
 * Private
 */




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




/**
 * Public
 */




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




void change_colors(PALETTE *palette)
{
  set_palette(*palette);
}




void find_screen_update_method(char *method)
{
  switch (get_update_method()) {
  case UPDATE_TRIPLE_BUFFER:
    strcpy(method, "Triple Buffering");
    break;
  case UPDATE_PAGE_FLIP:
    strcpy(method, "Page Flipping");
    break;
  case UPDATE_SYSTEM_BUFFER:
    strcpy(method, "System Buffering");
    break;
  case UPDATE_DOUBLE_BUFFER:
    strcpy(method, "Double Buffering");
    break;
  default:
    strcpy(method, "Unknown");
  }
}




int grab_screen_width()
{
  if (screen) {
    return screen->w;
  }
  
  return 0;
}




int grab_screen_height()
{
  if (screen) {
    return screen->h;
  }
  
  return 0;
}




int grab_canvas_width()
{
  if (canvas) {
    return canvas->w;
  }
  
  return 0;
}




void change_canvas_size(int width, int height)
{
  if (canvas) {
    destroy_bitmap(canvas);
  }
  
  canvas = create_bitmap(width, height);
  clear_to_color(canvas, makecol(0, 0, 0)); /* Black */
  update_scale();
}




int grab_canvas_height()
{
  if (canvas) {
    return canvas->h;
  }
  
  return 0;
}




BITMAP * grab_canvas()
{
  return canvas;
}




void refresh_screen()
{
  /**
   * Scale the window onto the screen.
   */
  stretch_blit(
    canvas,
    get_buffer(),
    0,
    0,
    grab_canvas_width(),
    grab_canvas_height(),
    (SCREEN_W / 2) - (grab_canvas_width() / 2 * scale),
    (SCREEN_H / 2) - (grab_canvas_height() / 2 * scale),
    grab_canvas_width() * scale,
    grab_canvas_height() * scale
  );
  
  /* Needed for Haiku */
  /*acquire_screen();*/
  
  update_screen();
  
  /* Needed for Haiku */
  /*release_screen();*/
}
