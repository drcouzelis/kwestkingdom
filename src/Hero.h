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
#import "Bow.h"
#import "Character.h"
#import "KeyControl.h"
#import "Resources.h"
#import "Shield.h"
#import "Sword.h"


#define MAX_HERO_HEALTH 3


@interface Hero : Character {
  
  Shield *shield;
  Sword *sword;
  Bow *bow;
  
  Animation *standAnimation;
  Animation *beginAttackAnimation;
  Animation *endAttackAnimation;
  Animation *hurtAnimation;
  Animation *deadAnimation;
  
  KeyControl *upKey;
  KeyControl *downKey;
  KeyControl *rightKey;
  KeyControl *leftKey;
  KeyControl *waitKey;
  KeyControl *attackKey;
  KeyControl *handKey;
  KeyControl *shieldKey;
  KeyControl *swordKey;
  KeyControl *bowKey;
  
  int direction;
  
}


- emptyHands;

// Updates
- updateStandState;

// State control
- toStandState;
- toMoveState;
- toAttackState;
- toHurtState;
- toDeadState;
- toPushSwordState;
- toPullSwordState;
- toDrawBowState;
- toShootArrowState;


@end
