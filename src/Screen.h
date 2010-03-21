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
#import "al_screen.h"
#import "KwestKingdom.h"


//#define SCREEN_WIDTH 640 // DEPRECATED
//#define SCREEN_HEIGHT 480 // DEPRECATED
//#define COLOR_DEPTH 8 // DEPRECATED
//#define TILE_SIZE 40 // DEPRECATED


BOOL startWindow(int w, int h);
BOOL startFullscreen(int w, int h);
void freeScreen();

void showScreen();

BITMAP * getBuffer();

int getScreenWidth();
int getScreenHeight();
int getScreenRatio();
int getScaledTileSize();

BOOL isFullscreen();
BOOL toggleFullscreen();

