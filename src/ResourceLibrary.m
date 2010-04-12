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


DATAFILE *resources = NULL;


void initializeResources() {
  if (resources) {
    destroyResources();
  }
  resources = load_datafile("resources.dat");
  if (resources == NULL) {
    fprintf(stderr, "Failed to initialize resources. \n");
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

