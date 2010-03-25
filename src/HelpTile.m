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
#import "HelpTile.h"


@implementation HelpTile


- init {
  
  self = [super init];
  
  if (self) {
    x = -1;
    y = -1;
    line1 = NULL;
    line2 = NULL;
    line3 = NULL;
    line4 = NULL;
    line5 = NULL;
    line6 = NULL;
    location = UPPER_LEFT;
  }
  
  return self;
  
}


- draw: (BITMAP *) buffer {
  
  int leftSide;
  int upperSide;
  int numOfLines;
  int lineSpacing;
  
  numOfLines = 6;
  lineSpacing = 10;
  
  if (location == UPPER_LEFT) {
    leftSide = 0;
    upperSide = 0;
  } else if (location == UPPER_RIGHT) {
    leftSide = getWindowWidth() / 2;
    upperSide = 0;
  } else if (location == LOWER_LEFT) {
    leftSide = 0;
    upperSide = getWindowHeight() / 2;
  } else {
    leftSide = getWindowWidth() / 2;
    upperSide = getWindowHeight() / 2;
  }
  
  leftSide += (getTileSize() / 2);
  upperSide += (getTileSize() / 2);
  
  drawBox(buffer, leftSide, upperSide, (getWindowWidth() / 2) - getTileSize(), (numOfLines + 2) * lineSpacing);
  
  if (line1) {
    resizedTextOut(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 1), 1, WHITE, line1);
  }
  
  if (line2) {
    resizedTextOut(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 2), 1, WHITE, line2);
  }
  
  if (line3) {
    resizedTextOut(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 3), 1, WHITE, line3);
  }
  
  if (line4) {
    resizedTextOut(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 4), 1, WHITE, line4);
  }
  
  if (line5) {
    resizedTextOut(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 5), 1, WHITE, line5);
  }
  
  if (line6) {
    resizedTextOut(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 6), 1, WHITE, line6);
  }
  
  
  return self;
  
}


- setX: (int) newX {
  x = newX;
  return self;
}


- setY: (int) newY {
  y = newY;
  return self;
}


- setLine1: (char *) newLine1
      and2: (char *) newLine2
      and3: (char *) newLine3
      and4: (char *) newLine4
      and5: (char *) newLine5
      and6: (char *) newLine6 {
  
  line1 = newLine1;
  line2 = newLine2;
  line3 = newLine3;
  line4 = newLine4;
  line5 = newLine5;
  line6 = newLine6;
  
  return self;
  
}


- (int) getX {
  return x;
}


- (int) getY {
  return y;
}


- setLocation: (int) theLocation {
  location = theLocation;
  return self;
}


@end

