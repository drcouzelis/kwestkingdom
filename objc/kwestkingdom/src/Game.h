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
#import <Foundation/Foundation.h>
#import "Animation.h"
#import "Drawable.h"
#import "EndlessWorld.h"
#import "HighScoreLibrary.h"
#import "KeyControl.h"
#import "KwestKingdom.h"
#import "Resources.h"
#import "RoomFactory.h"
#import "Snapshot.h"
#import "StoryWorld.h"
#import "Text.h"
#import "Updatable.h"


@interface Game : NSObject <Drawable, Updatable> {
  
  World *world;
  
  int state;
  
  Animation *titleAnimation;
  Animation *gameOverAnimation;
  
  KeyControl *fullscreenKey;
  KeyControl *soundKey;
  KeyControl *escapeKey;
  
  KeyControl *upKey;
  KeyControl *downKey;
  KeyControl *selectKey;
  
  int menuSelection;
  Snapshot *menuBackground;
  Snapshot *highScoresBackground;
  Animation *menuPointer;
  
  char playerInitials[4];
  
}


- readPlayerInitials;
- (BOOL) continuePlaying;
- activateMenuSelection;
- drawMenu: (BITMAP *) buffer;
- drawHighScores: (BITMAP *) buffer;
- drawEnterInitials: (BITMAP *) buffer;

- setState: (int) aState;

- gameOver;


@end
