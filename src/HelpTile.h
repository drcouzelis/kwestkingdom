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
#import "Drawable.h"
#import "KwestKingdom.h"
#import "Screen.h"
#import "Text.h"


typedef enum {
  UPPER_LEFT,
  UPPER_RIGHT,
  LOWER_LEFT,
  LOWER_RIGHT
} CORNER;


@interface HelpTile : Object <Drawable> {
  
  int x;
  int y;
  
  char *line1;
  char *line2;
  char *line3;
  char *line4;
  char *line5;
  char *line6;
  
  int location;
  
}


- setX: (int) newX;
- setY: (int) newY;

- setLine1: (char *) newLine1
      and2: (char *) newLine2
      and3: (char *) newLine3
      and4: (char *) newLine4
      and5: (char *) newLine5
      and6: (char *) newLine6;

- setLocation: (int) theLocation;

- (int) getX;
- (int) getY;


@end
