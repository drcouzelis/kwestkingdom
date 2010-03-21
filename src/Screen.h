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
#import "ResourceLibrary.h"


#define SCREEN_WIDTH 640 // DEPRECATED
#define SCREEN_HEIGHT 480 // DEPRECATED
#define COLOR_DEPTH 8 // DEPRECATED

#define TILE_SIZE 40 // DEPRECATED

#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480
#define DEFAULT_COLOR_DEPTH 8
#define DEFAULT_SCREEN_RATIO 2

#define ORIGINAL_TILE_SIZE 20

#define COLS 16
#define ROWS 12


int horizontalRoomTransitionSpeed;
int verticalRoomTransitionSpeed;

BOOL startWindow();
BOOL startFullscreen();
BOOL toggleFullscreen();
BOOL setColorDepth();
BITMAP * getBuffer();
void showScreen();

BOOL isFullscreen();
BOOL selectBestScreen();
int getScreenRatio();
int getTileSize();
void freeScreen();

