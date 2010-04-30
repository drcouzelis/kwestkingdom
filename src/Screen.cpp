/**
 * Copyright 2009 David Couzelis
 * 
 * This file is part of "Kwest Kingdom".
 * 
 * "Kwest Kingdom" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * "Kwest Kingdom" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with "Kwest Kingdom".  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

#include "al_screen.h"
#include "KwestKingdom.h"
#include "Screen.h"


#define DEFAULT_COLOR_DEPTH 8


// The window is the area inside the screen that
// the game is drawn on.
static BITMAP* window = NULL;

// The scale is used to know how big to multiply the window.
static int scale = DEFAULT_SCREEN_RATIO;


bool select_best_screen()
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
    std::cerr << "Failed to initialize screen updating." << std::endl;
    return false;
  }
  
  return true;
}


bool set_scale()
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

    return true;

  }
  
  return false;
}


void set_window_size(int width, int height)
{
  if (window) {
    destroy_bitmap(window);
  }
  
  window = create_bitmap(width, height);
  clear_to_color(window, BLACK);
  set_scale();
}


bool init_screen(int width, int height, bool fullscreen)
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
  
  // Start the screen.
  if (fullscreen) {
    
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, width, height, 0, 0)) {
      std::cerr << "Failed to set graphics mode to fullscreen ";
      std::cerr << width << "x" << height << "." << std::endl;
      return false;
    }
    
  } else {
  
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0)) {
      std::cerr << "Failed to set graphics mode to windowed ";
      std::cerr << width << "x" << height << "." << std::endl;
      return false;
    }

  }
  
  if (select_best_screen() == false) {
    return false;
  }

  set_scale();
  
  return true;
}
 

void free_screen()
{
  if (window) {
    destroy_bitmap(window);
    window = NULL;
  }
  shutdown_screen_updating();
}


int window_width()
{
  if (window) {
    return window->w;
  }
  return 0;
}


int window_height()
{
  if (window) {
    return window->h;
  }
  return 0;
}


bool show_screen()
{
  int x;
  int y;

  if (screen == NULL) {
    std::cerr << "Failed to find a screen to show." << std::endl;
    return false;
  }

  if (window == NULL) {
    std::cerr << "Failed to find a window to draw." << std::endl;
    return false;
  }

  x = getTileSize() / 5;
  y = window_height() - (getTileSize() / 2);
  
  switch (get_update_method()) {
  case UPDATE_TRIPLE_BUFFER:
    textprintf_ex(get_window(), font, x, y, WHITE, -1, "Triple Buffering");
    break;
  case UPDATE_PAGE_FLIP:
    textprintf_ex(get_window(), font, x, y, WHITE, -1, "Page Flipping");
    break;
  case UPDATE_SYSTEM_BUFFER:
    textprintf_ex(get_window(), font, x, y, WHITE, -1, "System Buffering");
    break;
  case UPDATE_DOUBLE_BUFFER:
    textprintf_ex(get_window(), font, x, y, WHITE, -1, "Double Buffering");
    break;
  }
  
  // Scale the window onto the screen.
  stretch_blit(
    get_window(),
    get_buffer(),
    0,
    0,
    window_width(),
    window_height(),
    (SCREEN_W / 2) - (window_width() / 2 * scale),
    (SCREEN_H / 2) - (window_height() / 2 * scale),
    window_width() * scale,
    window_height() * scale
  );
  
  update_screen();

  return true;
}
 

BITMAP* get_window()
{
  return window;
}

