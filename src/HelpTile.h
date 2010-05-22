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
#ifndef __HELP_TILE_H
#define __HELP_TILE_H


#include "Drawable.h"
#include "KwestKingdom.h"
#include "Screen.h"
#include "Text.h"


typedef enum {
  UPPER_LEFT,
  UPPER_RIGHT,
  LOWER_LEFT,
  LOWER_RIGHT
} CORNER;


class HelpTile : public virtual Drawable
{
public:
  HelpTile(int x, int y);
  
  virtual void draw(BITMAP* buffer); // Drawable
  
  void setLines(
    const char* line1 = NULL,
    const char* line2 = NULL,
    const char* line3 = NULL,
    const char* line4 = NULL,
    const char* line5 = NULL,
    const char* line6 = NULL
  );
  
  int getX();
  int getY();
  
protected:
  int x;
  int y;
  
  const char* line1;
  const char* line2;
  const char* line3;
  const char* line4;
  const char* line5;
  const char* line6;
};


#endif // __HELP_TILE_H
