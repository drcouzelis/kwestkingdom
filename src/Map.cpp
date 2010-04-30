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
#include "Map.h"


Map::Map()
  : cols(COLS),
    rows(ROWS)
{
  for (int x = 0; x < COLS - 1; x++) {
    for (int y = 0; y < ROWS - 1; y++) {
      map[x][y] = 0;
    }
  }
}


void
Map::set(int x, int y, int value)
{
  if (x >= 0 && x <= cols - 1 && y >= 0 && y <= rows - 1) {
    map[x][y] = value;
  }
}


int
Map::getValue(int x, int y)
{
  if (x >= 0 && x <= cols - 1 && y >= 0 && y <= rows - 1) {
    return map[x][y];
  }
  return 0;
}
