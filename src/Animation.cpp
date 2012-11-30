#include <stdio.h>
#include "Animation.h"


extern int timer;


Animation::Animation() {
  
  int i;
  
  for (i = 0; i < ANIMATION_MAX_FRAMES; i++) {
    frames[i] = NULL;
  }
  
  length = 0;
  pos = 0;
  loop = true;
  finished = false;
  speed = 0;
  fudge = 0;
  offsetX = 0;
  offsetY = 0;
  hFlip = false;
  vFlip = false;
  rotate = false;
}


Animation *
Animation::copy() {
  
  Animation *animation;
  int i;
  
  animation = new Animation();
  
  for (i = 0; i < length; i++) {
    animation->addFrame(frames[i]);
  }
  
  animation->setOffsetX(offsetX);
  animation->setOffsetY(offsetY);
  animation->setLoop(loop);
  animation->setSpeed(speed);
  animation->setHorizontalFlip(hFlip);
  animation->setVerticalFlip(vFlip);
  animation->setRotate(rotate);
  animation->reset();
  
  return animation;
}


void
Animation::reset() {
  pos = 0;
  finished = false;
  fudge = 0;
}


int
Animation::currentFrameNumber() {
  return pos;
}


bool
Animation::isFinished() {
  return finished;
}


BITMAP *
Animation::getImage() {
  if (length == 0) {
    return NULL;
  }
  return frames[pos];
}


void
Animation::addFrame(BITMAP *bitmap) {
  if (bitmap) {
    frames[length] = bitmap;
    length++;
  }
}


void
Animation::setSpeed(int newSpeed) {
  speed = newSpeed;
}


void
Animation::setLoop(bool loopOn) {
  loop = loopOn;
}


BITMAP *canvasStandardSize = NULL;
BITMAP *canvasTripleSize = NULL;


/**
 * This silly little function provides a fix for transparency
 * when using the rotate sprite and flip sprite functions.
 */
BITMAP *getCanvas(int width, int height) {
  
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

  fprintf(stderr, "Failed to find a canvas size %dx%d. \n", width, height);
  
  return NULL;
}


void
Animation::drawTo(BITMAP *buffer, int x, int y) {
  
  BITMAP *canvas;
  
  if (this->getImage() == NULL) {
    return;
  }
  
  // Write to a temporary canvas to get transparency
  // to work correctly.
  // Only necessary when rotating and flipping sprites.
  if (rotate || hFlip || vFlip) {
    canvas = getCanvas(this->getImage()->w, this->getImage()->h);
    if (canvas) {
      blit(this->getImage(), canvas, 0, 0, 0, 0, canvas->w, canvas->h);
    }
  } else {
    canvas = this->getImage();
  }
  
  if (canvas == NULL) {
    return;
  }
  
  if (rotate && hFlip && vFlip) {
    rotate_sprite(buffer, canvas, x + offsetX, y + offsetY, itofix(192));
  } else if (rotate && hFlip) {
    rotate_sprite_v_flip(buffer, canvas, x + offsetX, y + offsetY, itofix(192));
  } else if (rotate && vFlip) {
    rotate_sprite_v_flip(buffer, canvas, x + offsetX, y + offsetY, itofix(64));
  } else if (rotate) {
    rotate_sprite(buffer, canvas, x + offsetX, y + offsetY, itofix(64));
  } else if (hFlip && vFlip) {
    rotate_sprite(buffer, canvas, x + offsetX, y + offsetY, itofix(128));
  } else if (hFlip) {
    draw_sprite_h_flip(buffer, canvas, x + offsetX, y + offsetY);
  } else if (vFlip) {
    draw_sprite_v_flip(buffer, canvas, x + offsetX, y + offsetY);
  } else {
    draw_sprite(buffer, canvas, x + offsetX, y + offsetY);
  }
}


// Animate the animation.
void
Animation::update() {
  
  if (length > 1 && speed != 0) {
    
    fudge += speed;
    
    while (fudge >= GAME_TICKER) {
      
      pos++;
      
      if (pos == length) {
        if (loop) {
          pos = 0;
        } else {
          pos--;
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
Animation::setOffsetX(int newOffsetX) {
  offsetX = newOffsetX;
}


void
Animation::setOffsetY(int newOffsetY) {
  offsetY = newOffsetY;
}


int
Animation::width() {
  if (this->getImage() != NULL) {
    return this->getImage()->w;
  }
  return 0;
}


int
Animation::height() {
  if (this->getImage() != NULL) {
    return this->getImage()->h;
  }
  return 0;
}


void
Animation::setRotate(bool rotateOn) {
  rotate = rotateOn;
}


void
Animation::setHorizontalFlip(bool hFlipOn) {
  hFlip = hFlipOn;
}


void
Animation::setVerticalFlip(bool vFlipOn) {
  vFlip = vFlipOn;
}

