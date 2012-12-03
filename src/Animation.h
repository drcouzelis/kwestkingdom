#ifndef ANIMATION_HEADER
#define ANIMATION_HEADER


#include <allegro.h>
#include "KwestKingdom.h"
#include "Updatable.h"


#define ANIMATION_MAX_FRAMES 16


class Animation : public Updatable {

  BITMAP *frames[ANIMATION_MAX_FRAMES];
  
  // An animation is drawn with respect to its offset.
  int offsetX;
  int offsetY;

  int length;
  int pos;
  bool loop;
  bool finished;
  
  int speed;
  int fudge;
  
  bool hFlip;
  bool vFlip;
  bool rotate;

public:
  Animation();

  void update();

  BITMAP *getImage();
 
  void addFrame(BITMAP *bitmap);
 
  void setLoop(bool loopOn);
  void setSpeed(int newSpeed);
  void setOffsetX(int newOffsetX);
  void setOffsetY(int newOffsetY);
  void setRotate(bool rotateOn);
  void setHorizontalFlip(bool hFlipOn);
  void setVerticalFlip(bool vFlipOn);
 
  void reset();
 
  void drawTo(BITMAP *buffer, int x, int y);
  Animation *copy();
 
  bool isFinished();
  int width();
  int height();
  int currentFrameNumber();
};


#endif
