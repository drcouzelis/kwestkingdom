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
#import "Animation.h"


extern int timer;


@implementation Animation


- init {
  
  int i;
  
  self = [super init];
  
  if (self) {

    for (i = 0; i < ANIMATION_MAX_FRAMES; i++) {
      frames[i] = NULL;
    }
    
    length = 0;
    pos = 0;
    loop = YES;
    finished = NO;
    speed = 0;
    fudge = 0;
    offsetX = 0;
    offsetY = 0;
    hFlip = NO;
    vFlip = NO;
    rotate = NO;

  }
    
  return self;

}


- (Animation *) copy {
  
  Animation *animation;
  int i;
  
  animation = [[Animation alloc] init];
  
  for (i = 0; i < length; i++) {
    [animation addFrame: frames[i]];
  }
  
  [animation setOffsetX: offsetX];
  [animation setOffsetY: offsetY];
  [animation setLoop: loop];
  [animation setSpeed: speed];
  [animation setHorizontalFlip: hFlip];
  [animation setVerticalFlip: vFlip];
  [animation setRotate: rotate];
  [animation reset];
  
  return animation;
  
}


- reset {
  pos = 0;
  finished = NO;
  fudge = 0;
  return self;
}


- (int) currentFrameNumber {
  return pos;
}


- (BOOL) finished {
  return finished;
}


- (BITMAP *) getImage {
  if (length == 0) {
    return NULL;
  }
  return frames[pos];
}


- addFrame: (BITMAP *) bitmap {
  if (bitmap) {
    frames[length] = bitmap;
    length++;
  }
  return self;
}


- setSpeed: (int) newSpeed {
  speed = newSpeed;
  return self;
}


- setLoop: (BOOL) loopOn {
  loop = loopOn;
  return self;
}


BITMAP *canvasStandardSize = NULL;
BITMAP *canvasTripleSize = NULL;


/**
 * This silly little function provides a fix for transparency
 * when using the rotate sprite and flip sprite functions.
 */
BITMAP * getCanvas(int width, int height) {
  
  if (width == getTileSize() && height == getTileSize()) {
    if (canvasStandardSize == NULL) {
      canvasStandardSize = create_bitmap(getTileSize(), getTileSize());
    }
    return canvasStandardSize;
  }
  
  if (width == getTileSize() * 3 && height == getTileSize() * 3) {
    if (canvasTripleSize == NULL) {
      canvasTripleSize = create_bitmap(getTileSize() * 3, getTileSize() * 3);
    }
    return canvasTripleSize;
  }

  fprintf(stderr, "Failed to find a canvas size %dx%d. \n", width, height);
  
  return NULL;
  
}


- drawTo: (BITMAP *) buffer atX: (int) x andY: (int) y {
  
  BITMAP *canvas;
  
  if ([self getImage] == NULL) {
    return self;
  }
  
  // Write to a temporary canvas to get transparency
  // to work correctly.
  // Only necessary when rotating and flipping sprites.
  if (rotate || hFlip || vFlip) {
    canvas = getCanvas([self getImage]->w, [self getImage]->h);
    if (canvas) {
      blit([self getImage], canvas, 0, 0, 0, 0, canvas->w, canvas->h);
    }
  } else {
    canvas = [self getImage];
  }
  
  if (canvas == NULL) {
    return self;
  }
  
  if (rotate && hFlip && vFlip) {
    rotate_sprite(buffer, canvas, x + offsetX, y + offsetY, itofix(192));
  } else if (rotate && hFlip) {
    rotate_sprite_v_flip(buffer, canvas, x + offsetX, y + offsetY, itofix(192));
  } else if (rotate && vFlip) {
    rotate_sprite_v_flip(buffer, canvas, x + offsetX, y + offsetY, itofix(64));
  } else if (rotate) {
    rotate_sprite(buffer, canvas, x + offsetX, y + offsetY, itofix(64));
  } else if (hFlip && vFlip) {
    rotate_sprite(buffer, canvas, x + offsetX, y + offsetY, itofix(128));
  } else if (hFlip) {
    draw_sprite_h_flip(buffer, canvas, x + offsetX, y + offsetY);
  } else if (vFlip) {
    draw_sprite_v_flip(buffer, canvas, x + offsetX, y + offsetY);
  } else {
    draw_sprite(buffer, canvas, x + offsetX, y + offsetY);
  }
  
  return self;
  
}


// Animate the animation.
- update {
  
  if (length > 1 && speed != 0) {
    
    fudge += speed;
    
    while (fudge >= GAME_TICKER) {
      
      pos++;
      
      if (pos == length) {
        if (loop) {
          pos = 0;
        } else {
          pos--;
          finished = YES;
        }
      }
            
      fudge -= GAME_TICKER;
      
    }
    
  } else {
    
    finished = YES;
    
  }
  
  return self;

}


- setOffsetX: (int) newOffsetX {
  offsetX = newOffsetX;
  return self;
}


- setOffsetY: (int) newOffsetY {
  offsetY = newOffsetY;
  return self;
}


- (int) width {
  if ([self getImage] != NULL) {
    return [self getImage]->w;
  }
  return 0;
}


- (int) height {
  if ([self getImage] != NULL) {
    return [self getImage]->h;
  }
  return 0;
}


- setRotate: (BOOL) rotateOn {
  rotate = rotateOn;
  return self;
}


- setHorizontalFlip: (BOOL) hFlipOn {
  hFlip = hFlipOn;
  return self;
}


- setVerticalFlip: (BOOL) vFlipOn {
  vFlip = vFlipOn;
  return self;
}


@end

