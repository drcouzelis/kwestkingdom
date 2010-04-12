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
#import <objc/Object.h>
#import <allegro.h>
#import "ResourceLibrary.h"
#import "KwestKingdom.h"
#import "Updatable.h"


#define ANIMATION_MAX_FRAMES 16


@interface Animation : Object <Updatable> {

  BITMAP *frames[ANIMATION_MAX_FRAMES];
  
  // An animation is drawn with respect to its offset.
  int offsetX;
  int offsetY;

  int length;
  int pos;
  BOOL loop;
  BOOL finished;
  
  int speed;
  int fudge;
  
  BOOL hFlip;
  BOOL vFlip;
  BOOL rotate;

}

- (BITMAP *) getImage;

- addFrame: (BITMAP *) bitmap;

- setLoop: (BOOL) loopOn;
- setSpeed: (int) newSpeed;
- setOffsetX: (int) newOffsetX;
- setOffsetY: (int) newOffsetY;
- setRotate: (BOOL) rotateOn;
- setHorizontalFlip: (BOOL) hFlipOn;
- setVerticalFlip: (BOOL) vFlipOn;

- reset;

- drawTo: (BITMAP *) buffer atX: (int) x andY: (int) y;
- (Animation *) copy;

- (BOOL) finished;
- (int) width;
- (int) height;
- (int) currentFrameNumber;


@end

