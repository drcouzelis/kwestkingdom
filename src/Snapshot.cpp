#include "KwestKingdom.h"
#include "screen.h"
#include "Snapshot.h"


Snapshot::Snapshot() {
  canvas = create_bitmap(get_win_w(), get_win_h());
}


Snapshot::~Snapshot() {
  destroy_bitmap(canvas);

}


void Snapshot::update() {
  
  if (this->moving()) {
    
    if (speed > 0) {
      
      fudge += speed;
      
      while (fudge >= GAME_TICKER) {
        if (visualX != x) {
          if (visualX < x) {
            visualX++;
          } else {
            visualX--;
          }
        }
        if (visualY != y) {
          if (visualY < y) {
            visualY++;
          } else {
            visualY--;
          }
        }
        fudge -= GAME_TICKER;
      }
      
    } else {
      visualX = x;
      visualY = y;
    }
    
    if (!this->moving()) {
      fudge = 0;
    }
    
  }
  

  
}


void Snapshot::draw(IMAGE * canvas) {
  draw_sprite(canvas, this->getCanvas(), visualX, visualY);

}


IMAGE * Snapshot::getCanvas() {
  return canvas;
}


bool Snapshot::moving() {
  if (visualX != x || visualY != y) {
    return true;
  }
  return false;
}


void Snapshot::setX(int newX) {
  x = newX;
  visualX = x;

}


void Snapshot::setY(int newY) {
  y = newY;
  visualY = y;

}



