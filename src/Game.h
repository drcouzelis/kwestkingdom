#import <objc/Object.h>
#import "Animation.h"
#import "EndlessWorld.h"
#import "HighScoreLibrary.h"
#import "KeyControl.h"
#import "KwestKingdom.h"
#import "Resources.h"
#import "RoomFactory.h"
#import "Snapshot.h"
#import "StoryWorld.h"
#import "Text.h"


@interface Game : Object {
  
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

- update;
- draw:(BITMAP *)buffer;


@end
