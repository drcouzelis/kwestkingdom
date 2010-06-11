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
#import "Heart.h"


@implementation Heart


- init {
  
  self = [super init];
  
  if (self) {
    animation = [[Animation alloc] init];
    [animation addFrame: getImage(IMG_ITEMS_HEART)];
  }
  
  return self;
  
}


- collectedBy: (id<Livable, Moneyable>) character {
  [character setHealth: [character getHealth] + 1];
  playSound(SND_HEART);
  return self;
}


@end
