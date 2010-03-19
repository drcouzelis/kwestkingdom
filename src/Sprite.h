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
#import "Animation.h"
#import "Drawable.h"
#import "Inhabitable.h"
#import "Main.h"
#import "Positionable.h"
#import "ResourceLibrary.h"
#import "Screen.h"
#import "Targetable.h"
#import "Traversable.h"
#import "Updatable.h"


@interface Sprite : Object <Drawable, Positionable, Updatable> {
  
  // Position on the map
  int x; // Horizontal, from 0 to COLS - 1
  int y; // Vertical, from 0 to ROWS - 1
  int w; // Width of the sprite, or, how many square it occupies horizontally
  int h; // Height of the sprite
  
  // Where the image is on the screen
  int visualX; // SCREEN_WIDTH
  int visualY; // SCREEN_HEIGHT
  int fudge;
  
  int speed; // In FPS
  
  Animation *animation;
  
  id<Inhabitable, Targetable, Traversable> world;
  
  int state;
  
}


- (BOOL) moving;
- (int) getWidth;
- (int) getHeight;

- setWorld: (id<Inhabitable, Targetable, Traversable>) aWorld;
- setSpeed: (int) theSpeed;
- setState: (int) aState;


@end
