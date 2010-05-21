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
#include <iostream>

#include "Animation.h"
#include "KwestKingdom.h"


extern int timer;


Animation::Animation(int speed, bool loop)
: index(0)
, loop(loop)
, finished(false)
, speed(speed)
, fudge(0)
, hFlip(false)
, vFlip(false)
, rotate(false)
, hOffset(0)
, vOffset(0)
{
  // Empty
}


BITMAP* canvasStandardSize = NULL;
BITMAP* canvasTripleSize = NULL;


/**
 * This silly little function provides a fix for transparency
 * when using the rotate sprite and flip sprite functions.
 */
BITMAP*
getCanvas(int width, int height)
{
  if (width == getTileSize() && height == getTileSize()) {
    if (canvasStandardSize == NULL) {
      canvasStandardSize = create_bitmap(getTileSize(), getTileSize());
    }
    return canvasStandardSize;
  }
  
  if (width == getTileSize() * 3 && height == getTileSize() * 3) {
    if (canvasTripleSize == NULL) {
      canvasTripleSize = create_bitmap(getTileSize() * 3, getTileSize() * 3);
    }
    return canvasTripleSize;
  }
  
  std::cerr << "Failed to find a canvas size";
  std::cerr << width << "x" << height << std::endl;
  
  return NULL;
}


void
Animation::draw(BITMAP* buffer, int x, int y)
{
  if (getImage() == NULL) {
    return;
  }
  
  BITMAP* canvas;
  
  // Write to a temporary canvas to get transparency
  // to work correctly.
  // Only necessary when rotating and flipping sprites.
  if (rotate || hFlip || vFlip) {
    canvas = getCanvas(getImage()->w, getImage()->h);
    if (canvas) {
      blit(getImage(), canvas, 0, 0, 0, 0, canvas->w, canvas->h);
    }
  } else {
    canvas = getImage();
  }
  
  if (canvas == NULL) {
    return;
  }
  
  if (rotate && hFlip && vFlip) {
    rotate_sprite(buffer, canvas, x + hOffset, y + vOffset, itofix(192));
  } else if (rotate && hFlip) {
    rotate_sprite_v_flip(buffer, canvas, x + hOffset, y + vOffset, itofix(192));
  } else if (rotate && vFlip) {
    rotate_sprite_v_flip(buffer, canvas, x + hOffset, y + vOffset, itofix(64));
  } else if (rotate) {
    rotate_sprite(buffer, canvas, x + hOffset, y + vOffset, itofix(64));
  } else if (hFlip && vFlip) {
    rotate_sprite(buffer, canvas, x + hOffset, y + vOffset, itofix(128));
  } else if (hFlip) {
    draw_sprite_h_flip(buffer, canvas, x + hOffset, y + vOffset);
  } else if (vFlip) {
    draw_sprite_v_flip(buffer, canvas, x + hOffset, y + vOffset);
  } else {
    draw_sprite(buffer, canvas, x + hOffset, y + vOffset);
  }
}


void
Animation::animate()
{
  if (!finished && frames.empty() == false && speed != 0) {
    
    fudge += speed;
    
    while (fudge >= GAME_TICKER) {
      
      index++;
      
      if (index == frames.size()) {
        if (loop) {
          index = 0;
        } else {
          index--;
          finished = true;
        }
      }
            
      fudge -= GAME_TICKER;
      
    }
    
  } else {
    
    finished = true;
    
  }
}


void
Animation::addFrame(BITMAP* image)
{
  if (image) {
    frames.push_back(image);
  }
}


void
Animation::reset()
{
  index = 0;
  fudge = 0;
  finished = false;
}


bool
Animation::isFinished()
{
  return finished;
}


Animation&
Animation::operator=(const Animation& animation)
{
  // Make sure you are not trying to make a copy of yourself.
  if (this == &animation) {
    return *this;
  }
  
  // Copy the list of images.
  frames  = animation.frames;
  loop    = animation.loop;
  speed   = animation.speed;
  hFlip   = animation.hFlip;
  vFlip   = animation.vFlip;
  rotate  = animation.rotate;
  hOffset = animation.hOffset;
  vOffset = animation.vOffset;
  
  reset();
  
  return *this;
}


BITMAP*
Animation::getImage()
{
  if (frames.empty()) {
    return NULL;
  }
  return frames[index];
}


int
Animation::getWidth()
{
  if (getImage()) {
    return getImage()->w;
  }
  return 0;
}


int
Animation::getHeight()
{
  if (getImage()) {
    return getImage()->h;
  }
  return 0;
}

  
int
Animation::getCurrentFrameNumber()
{
  return index;
}


void
Animation::setSpeed(int speed) {
  this->speed = speed;
}


void
Animation::setHorizontalFlip(bool hFlip)
{
  this->hFlip = hFlip;
}


void
Animation::setVerticalFlip(bool vFlip)
{
  this->vFlip = vFlip;
}


void
Animation::setRotate(bool rotate)
{
  this->rotate = rotate;
}


void
Animation::setHorizontalOffset(int hOffset)
{
  this->hOffset = hOffset;
}


void
Animation::setVerticalOffset(int vOffset)
{
  this->vOffset = vOffset;
}
