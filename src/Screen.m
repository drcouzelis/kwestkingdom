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


static BOOL fullscreen = NO;
static BOOL screenInitialized = NO;

static int screenWidth = 0;
static int screenHeight = 0;
static int screenRatio = 1;


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


BOOL setColorDepth() {

  int colorDepth;
  
  colorDepth = desktop_color_depth();
  if (colorDepth == 0) {
    colorDepth = DEFAULT_COLOR_DEPTH;
  }
  
  set_color_depth(colorDepth);

  return YES;
}


int calculateScreenRatio(int w, int h) {
  // You should take into consideration all different kinds
  // of screen widths and heights.
  return h / (ROWS * TILE_SIZE); // TEMP
}


void freeScreen() {
  shutdown_screen_updating();
}


BOOL toggleFullscreen() {
  
  if (fullscreen) {
    return startWindow(getScreenWidth(), getScreenHeight());
  }
  
  return startFullscreen(getScreenWidth(), getScreenHeight());
  
}


BOOL startWindow(int w, int h) {
  
  if (screenInitialized) {
    shutdown_screen_updating();
  }
  
  setColorDepth();
 
  if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, w, h, 0, 0)) {
    printf("Failed to set graphics mode to windowed %dx%d. \n", w, h);
    return NO;
  }

  screenWidth = w;
  screenHeight = h;
  screenRatio = calculateScreenRatio(w, h);
  
  if (selectBestScreen() == NO) {
    return NO;
  }
  
  fullscreen = NO;
  screenInitialized = YES;
  
  return YES;
  
}


BOOL startFullscreen(int w, int h) {
  
  if (screenInitialized) {
    shutdown_screen_updating();
  }
  
  setColorDepth();
 
  // Try to match the screen resolution of the user's desktop.
  //get_desktop_resolution(&screenWidth, &screenHeight); 

  if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, w, h, 0, 0)) {
    printf("Failed to set graphics mode to windowed %dx%d. \n", w, h);
    return NO;
  }
 
  screenWidth = w;
  screenHeight = h;
  screenRatio = calculateScreenRatio(w, h);
  
  if (selectBestScreen() == NO) {
    return NO;
  }
  
  fullscreen = YES;
  screenInitialized = YES;
  
  return YES;
  
}


void showScreen() {
  
  switch (get_update_method()) {
  case UPDATE_TRIPLE_BUFFER:
    textprintf_ex(get_buffer(), font, 10, getScreenHeight() - 20, WHITE, -1, "Triple Buffering");
    break;
  case UPDATE_PAGE_FLIP:
    textprintf_ex(get_buffer(), font, 10, getScreenHeight() - 20, WHITE, -1, "Page Flipping");
    break;
  case UPDATE_SYSTEM_BUFFER:
    textprintf_ex(get_buffer(), font, 10, getScreenHeight() - 20, WHITE, -1, "System Buffering");
    break;
  case UPDATE_DOUBLE_BUFFER:
    textprintf_ex(get_buffer(), font, 10, getScreenHeight() - 20, WHITE, -1, "Double Buffering");
    break;
  }
  
  update_screen();
  
}


BITMAP * getBuffer() {
  return get_buffer();
}


int getScreenRatio() {
  return screenRatio;
}


int getScaledTileSize() {
  return TILE_SIZE * screenRatio;
}


int getScreenWidth() {
  return screenWidth;
}


int getScreenHeight() {
  return screenHeight;
}


BOOL isFullscreen() {
  return fullscreen;
}


