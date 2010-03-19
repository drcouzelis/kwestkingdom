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
#define ALLEGRO_STATICLINK 1


#import <objc/Object.h>
#import <allegro.h>


#define GAME_TICKER 100


#define WHITE (makecol(255, 255, 255)) //2
#define BLACK (makecol(0, 0, 0)) //1
//#define GREEN (makecol(0, 255, 0))
#define BLUE (makecol(0, 0, 100))
#define LIGHT_BLUE (makecol(130, 229, 255))
#define RED (makecol(109, 4, 4))
#define GRAY (makecol(109, 109, 109))

typedef enum {
  UP,
  DOWN,
  LEFT,
  RIGHT
} DIRECTION;


void game_over();

int random_number(int low, int high);
