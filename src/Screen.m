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

static int screenWidth = DEFAULT_SCREEN_WIDTH;
static int screenHeight = DEFAULT_SCREEN_HEIGHT;
static int screenRatio = DEFAULT_SCREEN_RATIO;


BOOL selectBestScreen() {
  
  horizontalRoomTransitionSpeed = screenWidth;
  verticalRoomTransitionSpeed = screenHeight;
  
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


void freeScreen() {
  destroyScaledImages();
  shutdown_screen_updating();
}


BOOL toggleFullscreen() {
  
  if (fullscreen) {
    return startWindow();
  }
  
  return startFullscreen();
  
}


BOOL startWindow() {
  
  if (screenInitialized) {
    shutdown_screen_updating();
  }
  
  setColorDepth();
 
  // If the game is running in a window then
  // just use the default scren resolution.
  screenWidth = DEFAULT_SCREEN_WIDTH;
  screenHeight = DEFAULT_SCREEN_HEIGHT;
  screenRatio = DEFAULT_SCREEN_RATIO;

  if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, screenWidth, screenHeight, 0, 0)) {
    printf("Failed to set graphics mode to windowed %dx%d. \n", screenWidth, screenHeight);
    return NO;
  }
  
  if (selectBestScreen() == NO) {
    return NO;
  }
  
  setPalette();
  initializeScaledImages();

  fullscreen = NO;
  screenInitialized = YES;
  
  return YES;
  
}


BOOL startFullscreen() {
  
  if (screenInitialized) {
    shutdown_screen_updating();
  }
  
  setColorDepth();
 
  // Try to match the screen resolution of the user's desktop.
  if (get_desktop_resolution(&screenWidth, &screenHeight) == 0) {
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, screenWidth, screenHeight, 0, 0)) {
      printf("Failed to set graphics mode to windowed %dx%d. \n", screenWidth, screenHeight);
      return NO;
    }
  } else {
    printf("Failed to get the desktop resolution. \n");
    return NO;
  }
  
  if (selectBestScreen() == NO) {
    return NO;
  }
  
  setPalette();
  initializeScaledImages();

  fullscreen = YES;
  screenInitialized = YES;
  
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


void showScreen() {
  
  switch (get_update_method()) {
  case UPDATE_TRIPLE_BUFFER:
    textprintf_ex(get_buffer(), font, 10, SCREEN_HEIGHT - 20, WHITE, -1, "Triple Buffering");
    break;
  case UPDATE_PAGE_FLIP:
    textprintf_ex(get_buffer(), font, 10, SCREEN_HEIGHT - 20, WHITE, -1, "Page Flipping");
    break;
  case UPDATE_SYSTEM_BUFFER:
    textprintf_ex(get_buffer(), font, 10, SCREEN_HEIGHT - 20, WHITE, -1, "System Buffering");
    break;
  case UPDATE_DOUBLE_BUFFER:
    textprintf_ex(get_buffer(), font, 10, SCREEN_HEIGHT - 20, WHITE, -1, "Double Buffering");
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


int getTileSize() {
  return ORIGINAL_TILE_SIZE * screenRatio;
}


BOOL isFullscreen() {
  return fullscreen;
}


