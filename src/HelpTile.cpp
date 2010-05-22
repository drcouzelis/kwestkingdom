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
#include "HelpTile.h"


HelpTile::HelpTile(int x, int y)
  : x(x),
    y(y),
    line1(NULL),
    line2(NULL),
    line3(NULL),
    line4(NULL),
    line5(NULL),
    line6(NULL)
{
  // Empty
}


void
HelpTile::draw(BITMAP* buffer)
{
  int leftSide;
  int upperSide;
  int numOfLines;
  int lineSpacing;
  int width;
  int height;
  
  numOfLines = 6;
  lineSpacing = 10;
  
  leftSide = 0;
  upperSide = 0;
 
  leftSide += (getTileSize() / 2);
  upperSide += (getTileSize() / 2);

  width = window_width() - (getTileSize() * 4);
  height = (numOfLines + 2) * lineSpacing;
  
  draw_box(buffer, leftSide, upperSide, leftSide + width, upperSide + height);
  
  if (line1) {
    resized_text_out(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 1), 1, WHITE, line1);
  }
  
  if (line2) {
    resized_text_out(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 2), 1, WHITE, line2);
  }
  
  if (line3) {
    resized_text_out(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 3), 1, WHITE, line3);
  }
  
  if (line4) {
    resized_text_out(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 4), 1, WHITE, line4);
  }
  
  if (line5) {
    resized_text_out(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 5), 1, WHITE, line5);
  }
  
  if (line6) {
    resized_text_out(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 6), 1, WHITE, line6);
  }
}


void
HelpTile::setLines(
  const char* line1,
  const char* line2,
  const char* line3,
  const char* line4,
  const char* line5,
  const char* line6
)
{
  this->line1 = line1;
  this->line2 = line2;
  this->line3 = line3;
  this->line4 = line4;
  this->line5 = line5;
  this->line6 = line6;
}


int
HelpTile::getX()
{
  return x;
}


int
HelpTile::getY()
{
  return y;
}
