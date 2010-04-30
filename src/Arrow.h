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
#ifndef __ARROW_H
#define __ARROW_H


#include "Character.h"


class Arrow : public Character
{
public:
  Arrow();
  ~Arrow();
  
  virtual void update(); // Updatable
  
  virtual bool isInsideScreen();
  virtual void findTarget();
  virtual void setDirection(int direction);
  
  virtual bool isStopped();
  
  // Deprecated
  virtual void toHoldState();
  virtual void toFlyingState();
  virtual void toStoppedState();
  
protected:
  Animation* flyUpAnimation;
  Animation* flyDownAnimation;
  Animation* flyLeftAnimation;
  Animation* flyRightAnimation;
  
  int direction;
};


#endif // __ARROW_H
