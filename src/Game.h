#ifndef GAME_HEADER
#define GAME_HEADER


#include <Foundation/Foundation.h>
#include "Animation.h"
#include "Drawable.h"
#include "EndlessWorld.h"
#include "HighScoreLibrary.h"
#include "KeyControl.h"
#include "KwestKingdom.h"
#include "Resources.h"
#include "RoomFactory.h"
#include "Snapshot.h"
#include "StoryWorld.h"
#include "Text.h"
#include "Updatable.h"


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


#endif