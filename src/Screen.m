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
#import "Screen.h"


#define DEFAULT_COLOR_DEPTH 8


// The window is the area inside the screen that
// the game is drawn on.
static BITMAP *window = NULL;

// The scale is used to know how big to multiply the window.
static int scale = 2;


// This function is not really necessary, is it?
//BOOL toggleFullscreen();
//  return initializeScreen(getScreenWidth(), getScreenHeight(), !fullscreen);
//}

 
BOOL selectBestScreen() {
  
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
    return NO;
  }
  
  return YES;
  
}


void setWindowSize(int width, int height) {
  if (window) {
    destroy_bitmap(window);
  }
  window = create_bitmap(width, height);
  clear_to_color(window, makecol(0, 0, 0)); // Clear to black
}


BOOL initializeScreen(int width, int height, BOOL fullscreen) {

  if (screen) {
    shutdown_screen_updating();
  }
  
  // Set the color depth.
  if (desktop_color_depth() == 0) {
    set_color_depth(DEFAULT_COLOR_DEPTH);
  } else {
    set_color_depth(desktop_color_depth());
  }
 
  // Start the screen.
  if (fullscreen) {
    
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, width, height, 0, 0)) {
      printf("Failed to set graphics mode to fullscreen %dx%d. \n", width, height);
      return NO;
    }
    
  } else {
  
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0)) {
      printf("Failed to set graphics mode to windowed %dx%d. \n", width, height);
      return NO;
    }

  }
  
  if (selectBestScreen() == NO) {
    return NO;
  }
  
  return YES;

}
 

void destroyScreen() {
  if (window) {
    destroy_bitmap(window);
    window = NULL;
  }
  shutdown_screen_updating();
}


int getWindowWidth() {
  if (window) {
    return window->w;
  }
  return 0;
}


int getWindowHeight() {
  if (window) {
    return window->h;
  }
  return 0;
}


void showScreen() {
  
  switch (get_update_method()) {
  case UPDATE_TRIPLE_BUFFER:
    textprintf_ex(getWindow(), font, 10, getWindowHeight() - 10, makecol(255, 255, 255), -1, "Triple Buffering");
    break;
  case UPDATE_PAGE_FLIP:
    textprintf_ex(getWindow(), font, 10, getWindowHeight() - 10, makecol(255, 255, 255), -1, "Page Flipping");
    break;
  case UPDATE_SYSTEM_BUFFER:
    textprintf_ex(getWindow(), font, 10, getWindowHeight() - 10, makecol(255, 255, 255), -1, "System Buffering");
    break;
  case UPDATE_DOUBLE_BUFFER:
    textprintf_ex(getWindow(), font, 10, getWindowHeight() - 10, makecol(255, 255, 255), -1, "Double Buffering");
    break;
  }
  
  // Scale the window onto the screen.
  stretch_blit(getWindow(), get_buffer(), 0, 0, getWindowWidth(), getWindowHeight(), 0, 0, getWindowWidth() * scale, getWindowHeight() * scale);
  
  update_screen();

}
 

BITMAP *getWindow() {
  return window;
}

