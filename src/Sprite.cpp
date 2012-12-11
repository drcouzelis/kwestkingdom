#include "Animation.h"
#include "KwestKingdom.h"
#include "Sprite.h"


Sprite::Sprite() {
  
  x = 0;
  y = 0;
  w = 1;
  h = 1;
  visualX = 0;
  visualY = 0;
  fudge = 0;
  speed = 0;
  animation = NULL;
  world = NULL;
  state = 0;
}


void Sprite::update() {
  
  if (animation != NULL) {
    animation->update();
  }
  
  // This will make the visual position of the sprite match up
  // with the actual position of the sprite at the right speed.
  if (this->moving()) {
    
    if (speed > 0) {
      
      fudge += speed;
      
      while (fudge >= GAME_TICKER) {
        if (visualX != x * getTileSize()) {
          if (visualX < x * getTileSize()) {
            visualX++;
          } else {
            visualX--;
          }
        }
        if (visualY != y * getTileSize()) {
          if (visualY < y * getTileSize()) {
            visualY++;
          } else {
            visualY--;
          }
        }
        fudge -= GAME_TICKER;
      }
      
    } else {
      visualX = x * getTileSize();
      visualY = y * getTileSize();
    }
    
    if (!this->moving()) {
      fudge = 0;
    }
  }
}


void Sprite::draw(BITMAP * buffer) {
  
  // Add a shadow.
  /*
  hline(buffer, visualX + 6, visualY + 30, visualX + 33, BLACK);
  hline(buffer, visualX + 6, visualY + 31, visualX + 33, BLACK);
  hline(buffer, visualX + 4, visualY + 32, visualX + 35, BLACK);
  hline(buffer, visualX + 4, visualY + 33, visualX + 35, BLACK);
  hline(buffer, visualX + 6, visualY + 34, visualX + 33, BLACK);
  hline(buffer, visualX + 6, visualY + 35, visualX + 33, BLACK);
  */
  
  if (animation != NULL) {
    animation->drawTo(buffer, visualX, visualY);
  }
}


bool Sprite::moving() {
  if (visualX != x * getTileSize() || visualY != y * getTileSize()) {
    return true;
  }
  return false;
}


void Sprite::bound(int top, int bottom, int left, int right) {
  
  if (x < left) {
    this->moveX(left);
  } else if (x + w - 1 > right) {
    this->moveX(right);
  }
  
  if (y < top) {
    this->moveY(top);
  } else if (y + h - 1 > bottom) {
    this->moveY(bottom);
  }
}


int Sprite::getX() {
  return x;
}


int Sprite::getY() {
  return y;
}


void Sprite::setX(int newX) {
  x = newX;
  visualX = x * getTileSize();
}


void Sprite::setY(int newY) {
  y = newY;
  visualY = y * getTileSize();
}


void Sprite::moveX(int newX) {
  x = newX;
}


void Sprite::moveY(int newY) {
  y = newY;
}


int Sprite::getWidth() {
  return w;
}


int Sprite::getHeight() {
  return h;
}


void Sprite::setWorld(World * aWorld) {
  world = aWorld;
}


void Sprite::setState(int aState) {
  state = aState;
}


void Sprite::setSpeed(int theSpeed) {
  speed = theSpeed;
}

