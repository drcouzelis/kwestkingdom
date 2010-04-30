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
#import "Arrow.h"


typedef enum {
  ARROW_HOLD_STATE,
  ARROW_FLYING_STATE,
  ARROW_STOPPED_STATE
} ARROW_STATE;


@implementation Arrow


- init {
  
  self = [super init];
  
  if (self) {
    
    [self setSpeed: getWalkSpeed() * 4];
    
    flyRightAnimation = [[Animation alloc] init];
    [flyRightAnimation addFrame: getImage(IMG_ARROW)];
    
    flyLeftAnimation = [[flyRightAnimation copy] setHorizontalFlip: YES];
    flyDownAnimation = [[flyRightAnimation copy] setRotate: YES];
    flyUpAnimation = [[[flyRightAnimation copy] setHorizontalFlip: YES] setRotate: YES];
    
    direction = UP;
    
    [self toHoldState];
    
  }
  
  return self;
  
}


- free {
  [flyUpAnimation free];
  [flyDownAnimation free];
  [flyLeftAnimation free];
  [flyRightAnimation free];
  return [super free];
}


- update {
  
  [super update];
  
  switch (state) {
  case ARROW_HOLD_STATE:
    // There's just not much going on when it's being held.
    break;
    
  case ARROW_FLYING_STATE:
    
    if (![self moving]) {
      
      if (direction == LEFT) {
        [world attackFromTeam: team atX: x - 1 andY: y];
      } else if (direction == RIGHT) {
        [world attackFromTeam: team atX: x + 1 andY: y];
      } else if (direction == UP) {
        [world attackFromTeam: team atX: x andY: y - 1];
      } else {
        [world attackFromTeam: team atX: x andY: y + 1];
      }
      
      [self toStoppedState];
      
    }
    
    break;
    
  case ARROW_STOPPED_STATE:
    // There's not much going on when it's stopped.
    break;
  }
  
  return self;
  
}


- (BOOL) isInsideScreen {
  if (x < 0 || x > COLS - 1 || y < 0 || y > ROWS - 1) {
    return NO;
  }
  return YES;
}


- findTarget {
  
  if (direction == LEFT) {
    while ([world isFlyableAtX: x - 1 andY: y] && ![world isAttackableFromTeam: team atX: x - 1 andY: y] && [self isInsideScreen]) {
      x--;
    }
  } else if (direction == RIGHT) {
    while ([world isFlyableAtX: x + 1 andY: y] && ![world isAttackableFromTeam: team atX: x + 1 andY: y] && [self isInsideScreen]) {
      x++;
    }
  } else if (direction == UP) {
    while ([world isFlyableAtX: x andY: y - 1] && ![world isAttackableFromTeam: team atX: x andY: y - 1] && [self isInsideScreen]) {
      y--;
    }
  } else {
    while ([world isFlyableAtX: x andY: y + 1] && ![world isAttackableFromTeam: team atX: x andY: y + 1] && [self isInsideScreen]) {
      y++;
    }
  }
  
  return self;
  
}


- setDirection: (int) aDirection {
  direction = aDirection;
  if (direction == UP) {
    animation = flyUpAnimation;
  } else if (direction == DOWN) {
    animation = flyDownAnimation;
  } else if (direction == LEFT) {
    animation = flyLeftAnimation;
  } else {
    animation = flyRightAnimation;
  }
  return self;
}


- toHoldState {
  
  int visualOffset;
  
  visualOffset = (getTileSize() / 3) + (getTileSize() / 10);
  
  state = ARROW_HOLD_STATE;
  
  [self setDirection: direction];
  
  // Offset the animation a little bit to make it look like
  // the arrow is in the bow string.
  [flyUpAnimation setOffsetX: 0];
  [flyUpAnimation setOffsetY: visualOffset];
  [flyDownAnimation setOffsetX: 0];
  [flyDownAnimation setOffsetY: -visualOffset];
  [flyLeftAnimation setOffsetX: visualOffset];
  [flyLeftAnimation setOffsetY: 0];
  [flyRightAnimation setOffsetX: -visualOffset];
  [flyRightAnimation setOffsetY: 0];
  
  return self;
}


- toFlyingState {
  state = ARROW_FLYING_STATE;
  [self setDirection: direction];
  [self findTarget];
  // Put the animation back to where it's supposed to be.
  [flyUpAnimation setOffsetX: 0];
  [flyUpAnimation setOffsetY: 0];
  [flyDownAnimation setOffsetX: 0];
  [flyDownAnimation setOffsetY: 0];
  [flyLeftAnimation setOffsetX: 0];
  [flyLeftAnimation setOffsetY: 0];
  [flyRightAnimation setOffsetX: 0];
  [flyRightAnimation setOffsetY: 0];
  playSound(SND_ARROW_FLY);
  return self;
}


- toStoppedState {
  state = ARROW_STOPPED_STATE;
  [self setDirection: direction];
  playSound(SND_ARROW_HIT);
  return self;
}


- (BOOL) stopped {
  if (state == ARROW_STOPPED_STATE) {
    return YES;
  }
  return NO;
}


@end
