#import "Chomper.h"
#import "World.h"


typedef enum {
  CHOMPER_STAND_STATE,
  CHOMPER_ATTACK_STATE,
  CHOMPER_MOVE_STATE
} CHOMPER_STATE;


@implementation Chomper


- init {
  
  self = [super init];
  
  if (self) {
    
    prevDirection = UP;
    
    standAnimation = [[Animation alloc] init];
    [standAnimation addFrame: getImage(IMG_CHOMPER_STAND_1)];
    [standAnimation addFrame: getImage(IMG_CHOMPER_STAND_2)];
    [standAnimation addFrame: getImage(IMG_CHOMPER_STAND_3)];
    [standAnimation addFrame: getImage(IMG_CHOMPER_STAND_2)];
    [standAnimation setLoop: YES];
    [standAnimation setSpeed: 6];
    
    attackAnimation = [[Animation alloc] init];
    [attackAnimation addFrame: getImage(IMG_CHOMPER_BITE_1)];
    [attackAnimation addFrame: getImage(IMG_CHOMPER_BITE_2)];
    [attackAnimation addFrame: getImage(IMG_CHOMPER_BITE_3)];
    [attackAnimation addFrame: getImage(IMG_CHOMPER_BITE_4)];
    [attackAnimation addFrame: getImage(IMG_CHOMPER_BITE_5)];
    [attackAnimation addFrame: getImage(IMG_CHOMPER_BITE_4)];
    [attackAnimation addFrame: getImage(IMG_CHOMPER_BITE_3)];
    [attackAnimation addFrame: getImage(IMG_CHOMPER_BITE_2)];
    [attackAnimation addFrame: getImage(IMG_CHOMPER_BITE_1)];
    [attackAnimation setLoop: NO];
    [attackAnimation setSpeed: 20];
    
    animation = standAnimation;
    state = CHOMPER_STAND_STATE;
    [self wait];
    
  }
  
  return self;
  
}


- free {
  [standAnimation free];
  [attackAnimation free];
  return [super free];
}


- update {
  
  int dir;
  int toX;
  int toY;
  Character *target;
  
  [super update];
  
  if ([self waiting]) {
    return self;
  }
  
  if (health == 0) {
    return self;
  }
  
  target = [world getTarget];
  
  switch (state) {
  
  case CHOMPER_STAND_STATE:
    
	// If the target has a walking distance of one...
    if (abs(x - [target getX]) + abs(y - [target getY]) == 1) {
	  
      state = CHOMPER_ATTACK_STATE;
      animation = attackAnimation;
      [animation reset];
      playSound(SND_CHOMP);
      
    } else {
      
      if (abs(x - [target getX]) < 4 && abs(y - [target getY]) < 4) {
        if (abs(x - [target getX]) < abs(y - [target getY])) {
          if (y - [target getY] > 0) {
            dir = UP;
          } else {
            dir = DOWN;
          }
        } else if (abs(x - [target getX]) > abs(y - [target getY])) {
          if (x - [target getX] > 0) {
            dir = LEFT;
          } else {
            dir = RIGHT;
          }
        } else {
          if (x - [target getX] < 0 && y - [target getY] > 0) { // NE
            if (prevDirection == UP) {
              dir = RIGHT;
            } else {
              dir = UP;
            }
          } else if (x - [target getX] < 0 && y - [target getY] < 0) { // SE
            if (prevDirection == DOWN) {
              dir = RIGHT;
            } else {
              dir = DOWN;
            }
          } else if (x - [target getX] > 0 && y - [target getY] > 0) { // NW
            if (prevDirection == UP) {
              dir = LEFT;
            } else {
              dir = UP;
            }
          } else { // SW
            if (prevDirection == DOWN) {
              dir = LEFT;
            } else {
              dir = DOWN;
            }
          }
        }
      } else {
        dir = random_number(UP, LEFT);
      }
      
      toX = x;
      toY = y;
      
      if (dir == UP) {
        toY--;
      } else if (dir == DOWN) {
        toY++;
      } else if (dir == RIGHT) {
        toX++;
      } else if (dir == LEFT) {
        toX--;
      }
      
      if ([world isWalkableAtX: toX andY: toY] && ![world isInhabitedAtX: toX andY: toY]) {
        [self moveX: toX];
        [self moveY: toY];
        state = CHOMPER_MOVE_STATE;
      }
      
      // Bound him so he doesn't wander right out of the screen!
      [self boundAtTop: 1 andBottom: ROWS - 2 andLeft: 1 andRight: COLS - 2];
      
      prevDirection = dir;
      
      [self wait];
      
    }
    
    break;
    
  case CHOMPER_MOVE_STATE:
    if (![self moving]) {
      state = CHOMPER_STAND_STATE;
    }
    break;
    
  case CHOMPER_ATTACK_STATE:
    if ([animation finished]) {
      [world attackFromTeam: team atX: [target getX] andY: [target getY]];
      state = CHOMPER_STAND_STATE;
      animation = standAnimation;
      [animation reset];
      [self wait];
    }
	break;
	
  }
  
  return self;
  
}


@end

