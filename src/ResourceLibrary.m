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
#import "ResourceLibrary.h"


// This array will hold the actual bitmaps that will be drawn to the screen.
// "PALETTE_PAL" is the last item in the list of resources. (See "Resources.h")
//static BITMAP *scaledImages[PALETTE_PAL];
//static BOOL scaledImagesInitialized = NO;


void resizedTextOut(BITMAP *dest, int x, int y, double multiplier, int color, char *text) {
  //BITMAP *tempBitmap;
  //tempBitmap = create_bitmap(text_length(font, text), text_height(font));
  //clear_to_color(tempBitmap, makecol(255, 0, 255));
  //textout_ex(tempBitmap, font, text, 0, 0, color, -1);
  //masked_stretch_blit(tempBitmap, dest, 0, 0, tempBitmap->w, tempBitmap->h, x, y, (int)(tempBitmap->w * multiplier), (int)(tempBitmap->h * multiplier)); 
  //destroy_bitmap(tempBitmap);
  textout_ex(dest, font, text, x, y, color, -1);
}


void drawBox(BITMAP *buffer, int x, int y, int w, int h) {
  
  int leftOutside;
  int rightOutside;
  int topOutside;
  int bottomOutside;
  
  int leftInside;
  int rightInside;
  int topInside;
  int bottomInside;
  
  int offset;
  int depth;
  
  offset = 4;
  depth = 12;
  
  leftOutside = x - offset;
  rightOutside = x + w + offset;
  topOutside = y - offset;
  bottomOutside = y + h + offset;
  
  leftInside = leftOutside + depth;
  rightInside = rightOutside - depth;
  topInside = topOutside + depth;
  bottomInside = bottomOutside - depth;
  
  rectfill(buffer, leftInside, topInside, rightInside, bottomInside, RED);
  
  // Top
  hline(buffer, leftOutside + 2, topOutside + 0, rightOutside - 2, WHITE);
  hline(buffer, leftOutside + 2, topOutside + 1, rightOutside - 2, WHITE);
  hline(buffer, leftOutside, topOutside + 2, rightOutside - 4, WHITE);
  hline(buffer, leftOutside, topOutside + 3, rightOutside - 4, WHITE);
  hline(buffer, leftOutside, topOutside + 4, leftOutside + 5, WHITE);
  hline(buffer, leftOutside, topOutside + 5, leftOutside + 5, WHITE);
  hline(buffer, leftOutside, topOutside + 6, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, topOutside + 7, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, topOutside + 8, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, topOutside + 9, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, topOutside + 10, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, topOutside + 11, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, topOutside + 12, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, topOutside + 13, leftOutside + 3, WHITE);
  hline(buffer, rightOutside - 9, topOutside + 10, rightOutside - 8, WHITE);
  hline(buffer, rightOutside - 9, topOutside + 11, rightOutside - 8, WHITE);
  hline(buffer, rightOutside - 11, topOutside + 12, rightOutside - 8, WHITE);
  hline(buffer, rightOutside - 11, topOutside + 13, rightOutside - 8, WHITE);
  
  hline(buffer, leftOutside + 6, topOutside + 4, rightOutside - 6, BLACK);
  hline(buffer, leftOutside + 6, topOutside + 5, rightOutside - 6, BLACK);
  hline(buffer, leftOutside + 4, topOutside + 6, rightOutside - 4, BLACK);
  hline(buffer, leftOutside + 4, topOutside + 7, rightOutside - 4, BLACK);
  hline(buffer, leftOutside + 4, topOutside + 8, leftOutside + 9, BLACK);
  hline(buffer, leftOutside + 4, topOutside + 9, leftOutside + 9, BLACK);
  hline(buffer, leftOutside + 4, topOutside + 10, leftOutside + 7, BLACK);
  hline(buffer, leftOutside + 4, topOutside + 11, leftOutside + 7, BLACK);
  hline(buffer, leftOutside + 4, topOutside + 12, leftOutside + 7, BLACK);
  hline(buffer, leftOutside + 4, topOutside + 13, leftOutside + 7, BLACK);
  hline(buffer, rightOutside - 7, topOutside + 8, rightOutside - 4, BLACK);
  hline(buffer, rightOutside - 7, topOutside + 9, rightOutside - 4, BLACK);
  hline(buffer, rightOutside - 7, topOutside + 10, rightOutside - 4, BLACK);
  hline(buffer, rightOutside - 7, topOutside + 11, rightOutside - 4, BLACK);
  hline(buffer, rightOutside - 7, topOutside + 12, rightOutside - 4, BLACK);
  hline(buffer, rightOutside - 7, topOutside + 13, rightOutside - 4, BLACK);
  
  hline(buffer, leftOutside + 10, topOutside + 8, rightOutside - 8, GRAY);
  hline(buffer, leftOutside + 10, topOutside + 9, rightOutside - 8, GRAY);
  hline(buffer, leftOutside + 8, topOutside + 10, rightOutside - 10, GRAY);
  hline(buffer, leftOutside + 8, topOutside + 11, rightOutside - 10, GRAY);
  hline(buffer, leftOutside + 8, topOutside + 12, leftOutside + 13, GRAY);
  hline(buffer, leftOutside + 8, topOutside + 13, leftOutside + 13, GRAY);
  hline(buffer, rightOutside - 13, topOutside + 12, rightOutside - 12, GRAY);
  hline(buffer, rightOutside - 13, topOutside + 13, rightOutside - 12, GRAY);
  hline(buffer, rightOutside - 3, topOutside + 2, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, topOutside + 3, rightOutside, GRAY);
  hline(buffer, rightOutside - 5, topOutside + 4, rightOutside, GRAY);
  hline(buffer, rightOutside - 5, topOutside + 5, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, topOutside + 6, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, topOutside + 7, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, topOutside + 8, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, topOutside + 9, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, topOutside + 10, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, topOutside + 11, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, topOutside + 12, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, topOutside + 13, rightOutside, GRAY);
  
  // Bottom
  hline(buffer, leftOutside + 2, bottomOutside - 0, rightOutside - 2, GRAY);
  hline(buffer, leftOutside + 2, bottomOutside - 1, rightOutside - 2, GRAY);
  hline(buffer, leftOutside + 2, bottomOutside - 2, rightOutside, GRAY);
  hline(buffer, leftOutside + 2, bottomOutside - 3, rightOutside, GRAY);
  hline(buffer, rightOutside - 5, bottomOutside - 4, rightOutside, GRAY);
  hline(buffer, rightOutside - 5, bottomOutside - 5, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, bottomOutside - 6, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, bottomOutside - 7, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, bottomOutside - 8, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, bottomOutside - 9, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, bottomOutside - 10, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, bottomOutside - 11, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, bottomOutside - 12, rightOutside, GRAY);
  hline(buffer, rightOutside - 3, bottomOutside - 13, rightOutside, GRAY);
  hline(buffer, leftOutside + 4, bottomOutside - 4, leftOutside + 5, GRAY);
  hline(buffer, leftOutside + 4, bottomOutside - 5, leftOutside + 5, GRAY);
  hline(buffer, leftOutside + 8, bottomOutside - 10, leftOutside + 11, GRAY);
  hline(buffer, leftOutside + 8, bottomOutside - 11, leftOutside + 11, GRAY);
  hline(buffer, leftOutside + 8, bottomOutside - 12, leftOutside + 11, GRAY);
  hline(buffer, leftOutside + 8, bottomOutside - 13, leftOutside + 11, GRAY);
  hline(buffer, leftOutside + 12, bottomOutside - 12, leftOutside + 13, GRAY);
  hline(buffer, leftOutside + 12, bottomOutside - 13, leftOutside + 13, GRAY);
  
  hline(buffer, leftOutside + 6, bottomOutside - 4, rightOutside - 6, BLACK);
  hline(buffer, leftOutside + 6, bottomOutside - 5, rightOutside - 6, BLACK);
  hline(buffer, leftOutside + 4, bottomOutside - 6, rightOutside - 4, BLACK);
  hline(buffer, leftOutside + 4, bottomOutside - 7, rightOutside - 4, BLACK);
  hline(buffer, rightOutside - 9, bottomOutside - 8, rightOutside - 4, BLACK);
  hline(buffer, rightOutside - 9, bottomOutside - 9, rightOutside - 4, BLACK);
  hline(buffer, rightOutside - 7, bottomOutside - 10, rightOutside - 4, BLACK);
  hline(buffer, rightOutside - 7, bottomOutside - 11, rightOutside - 4, BLACK);
  hline(buffer, rightOutside - 7, bottomOutside - 12, rightOutside - 4, BLACK);
  hline(buffer, rightOutside - 7, bottomOutside - 13, rightOutside - 4, BLACK);
  hline(buffer, leftOutside + 4, bottomOutside - 8, leftOutside + 7, BLACK);
  hline(buffer, leftOutside + 4, bottomOutside - 9, leftOutside + 7, BLACK);
  hline(buffer, leftOutside + 4, bottomOutside - 10, leftOutside + 7, BLACK);
  hline(buffer, leftOutside + 4, bottomOutside - 11, leftOutside + 7, BLACK);
  hline(buffer, leftOutside + 4, bottomOutside - 12, leftOutside + 7, BLACK);
  hline(buffer, leftOutside + 4, bottomOutside - 13, leftOutside + 7, BLACK);
  hline(buffer, leftOutside + 8, bottomOutside - 8, leftOutside + 9, BLACK);
  hline(buffer, leftOutside + 8, bottomOutside - 9, leftOutside + 9, BLACK);
  
  hline(buffer, leftOutside + 10, bottomOutside - 8, rightOutside - 10, WHITE);
  hline(buffer, leftOutside + 10, bottomOutside - 9, rightOutside - 10, WHITE);
  hline(buffer, leftOutside + 12, bottomOutside - 10, rightOutside - 8, WHITE);
  hline(buffer, leftOutside + 12, bottomOutside - 11, rightOutside - 8, WHITE);
  hline(buffer, rightOutside - 13, bottomOutside - 12, rightOutside - 8, WHITE);
  hline(buffer, rightOutside - 13, bottomOutside - 13, rightOutside - 8, WHITE);
  hline(buffer, leftOutside, bottomOutside - 2, leftOutside + 1, WHITE);
  hline(buffer, leftOutside, bottomOutside - 3, leftOutside + 1, WHITE);
  hline(buffer, leftOutside, bottomOutside - 4, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, bottomOutside - 5, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, bottomOutside - 6, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, bottomOutside - 7, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, bottomOutside - 8, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, bottomOutside - 9, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, bottomOutside - 10, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, bottomOutside - 11, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, bottomOutside - 12, leftOutside + 3, WHITE);
  hline(buffer, leftOutside, bottomOutside - 13, leftOutside + 3, WHITE);
  
  // Left
  vline(buffer, leftOutside + 0, topOutside + 14, bottomOutside - 14, WHITE);
  vline(buffer, leftOutside + 1, topOutside + 14, bottomOutside - 14, WHITE);
  vline(buffer, leftOutside + 2, topOutside + 14, bottomOutside - 14, WHITE);
  vline(buffer, leftOutside + 3, topOutside + 14, bottomOutside - 14, WHITE);
  vline(buffer, leftOutside + 4, topOutside + 14, bottomOutside - 14, BLACK);
  vline(buffer, leftOutside + 5, topOutside + 14, bottomOutside - 14, BLACK);
  vline(buffer, leftOutside + 6, topOutside + 14, bottomOutside - 14, BLACK);
  vline(buffer, leftOutside + 7, topOutside + 14, bottomOutside - 14, BLACK);
  vline(buffer, leftOutside + 8, topOutside + 14, bottomOutside - 14, GRAY);
  vline(buffer, leftOutside + 9, topOutside + 14, bottomOutside - 14, GRAY);
  vline(buffer, leftOutside + 10, topOutside + 14, bottomOutside - 14, GRAY);
  vline(buffer, leftOutside + 11, topOutside + 14, bottomOutside - 14, GRAY);
  
  // Right
  vline(buffer, rightOutside - 0, topOutside + 14, bottomOutside - 14, GRAY);
  vline(buffer, rightOutside - 1, topOutside + 14, bottomOutside - 14, GRAY);
  vline(buffer, rightOutside - 2, topOutside + 14, bottomOutside - 14, GRAY);
  vline(buffer, rightOutside - 3, topOutside + 14, bottomOutside - 14, GRAY);
  vline(buffer, rightOutside - 4, topOutside + 14, bottomOutside - 14, BLACK);
  vline(buffer, rightOutside - 5, topOutside + 14, bottomOutside - 14, BLACK);
  vline(buffer, rightOutside - 6, topOutside + 14, bottomOutside - 14, BLACK);
  vline(buffer, rightOutside - 7, topOutside + 14, bottomOutside - 14, BLACK);
  vline(buffer, rightOutside - 8, topOutside + 14, bottomOutside - 14, WHITE);
  vline(buffer, rightOutside - 9, topOutside + 14, bottomOutside - 14, WHITE);
  vline(buffer, rightOutside - 10, topOutside + 14, bottomOutside - 14, WHITE);
  vline(buffer, rightOutside - 11, topOutside + 14, bottomOutside - 14, WHITE);
  
}


DATAFILE *resources = NULL;


void initializeResources() {
  if (resources) {
    destroyResources();
  }
  resources = load_datafile("resources.dat");
  if (resources == NULL) {
    printf("Failed to initialize resources. \n");
  }
}


void destroyResources() {
  unload_datafile(resources);
}


void initializeScaledImages() {
  
  /*
  BITMAP *resource;
  BITMAP *canvas;
  int i;
  
  if (scaledImagesInitialized) {
    destroyScaledImages();
  }

  // "ARCHER_01_BMP" is the first bitmap in the list of resources.
  // "PALETTE_PAL" is the last one.
  for (i = ARCHER_01_BMP; i < PALETTE_PAL; i++) {
    
    resource = (BITMAP *)resources[i].dat;
    
    // Copy the resource bitmap to a temporary canvas
    // because only memory bitmaps can be scaled.
    canvas = create_bitmap(resource->w, resource->h);
    blit(resource, canvas, 0, 0, 0, 0, canvas->w, canvas->h);
    
    scaledImages[i] = create_bitmap(canvas->w * getScreenRatio(), canvas->h * getScreenRatio());
    clear_to_color(scaledImages[i], MAGICPINK);

    stretch_sprite(scaledImages[i], canvas, 0, 0, scaledImages[i]->w, scaledImages[i]->h);

    destroy_bitmap(canvas);
  }


  scaledImagesInitialized = YES;
  */

}


void destroyScaledImages() {
  /*
  int i;
  if (scaledImagesInitialized) {
    for (i = ARCHER_01_BMP; i < PALETTE_PAL; i++) {
      destroy_bitmap(scaledImages[i]);
    }
    scaledImagesInitialized = NO;
  }
  */
}


BITMAP * getImage(int image) {
  return (BITMAP *)resources[image].dat;
  /*
  if (scaledImagesInitialized) {
    return scaledImages[image];
  }
  return NULL;
  */
}


void setPalette(void) {
  set_palette(resources[PALETTE_PAL].dat);
}


void playSound(int sound) {
  play_sample((SAMPLE *)resources[sound].dat, 255, 128, 1000, 0);
}


#define GAME_VOLUME 192


void toggleSound(void) {
  
  int digiVolume;
  int midiVolume;
  
  get_volume(&digiVolume, &midiVolume);
  
  if (digiVolume == 0) {
    set_volume(GAME_VOLUME, GAME_VOLUME);
  } else {
    set_volume(0, 0);
  }
  
}


BOOL soundEnabled(void) {
  
  int digiVolume;
  int midiVolume;
  
  get_volume(&digiVolume, &midiVolume);
  
  if (digiVolume == 0) {
    return NO;
  }
  
  return YES;
  
}

