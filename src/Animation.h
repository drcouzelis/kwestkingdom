#ifndef ANIMATION_HEADER
#define ANIMATION_HEADER


#include <allegro.h>


#define ANIMATION_MAX_FRAMES 16


class Animation {

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
 
  Animation *setLoop(bool loopOn);
  Animation *setSpeed(int newSpeed);
  Animation *setOffsetX(int newOffsetX);
  Animation *setOffsetY(int newOffsetY);
  Animation *setRotate(bool rotateOn);
  Animation *setHorizontalFlip(bool hFlipOn);
  Animation *setVerticalFlip(bool vFlipOn);
 
  void reset();
 
  void drawTo(BITMAP *buffer, int x, int y);
  Animation *copy();
 
  bool isFinished();
  int width();
  int height();
  int currentFrameNumber();
};


#endif
