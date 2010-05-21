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
#ifndef __ANIMATION_H
#define __ANIMATION_H


#include <vector>
#include <allegro.h>


class Animation
{
public:
  Animation(int speed = 0, bool loop = false);
  
  /**
   * Animate the animation.
   */
  virtual void animate(); // Inherited
  
  /**
   * Draw the current frame to the specified buffer,
   * with the correct offsets.
   */
  virtual void draw(BITMAP* buffer, int x, int y);
  
  /**
   * Add an image to the end of the list of frames.
   */
  virtual void addFrame(BITMAP* image);
  
  /**
   * Reset the animation to the first frame.
   */
  virtual void reset();
  
  /**
   * This method is only relevant to animations that do not loop.
   */
  virtual bool isFinished();
  
  /**
   * Create a copy.
   */
  virtual Animation& operator=(const Animation& animation);
  
  /**
   * Get the current frame of animation.
   */
  virtual BITMAP* getImage();
  
  virtual int getWidth();
  virtual int getHeight();
  virtual int getCurrentFrameNumber();
  
  virtual void setSpeed(int speed);
  virtual void setHorizontalFlip(bool hFlip);
  virtual void setVerticalFlip(bool vFlip);
  virtual void setRotate(bool rotate);
  virtual void setHorizontalOffset(int hOffset);
  virtual void setVerticalOffset(int vOffset);
  
protected:
  std::vector<BITMAP*> frames;
  
  unsigned int index;
  bool         loop;
  bool         finished;
  
  int speed;
  int fudge;
  
  bool hFlip;
  bool vFlip;
  bool rotate;
  
  /**
   * An animation is drawn with respect to its offset.
   */
  int hOffset;
  int vOffset;
};


#endif // __ANIMATION_H
