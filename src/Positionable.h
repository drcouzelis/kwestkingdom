#ifndef POSITIONABLE_HEADER
#define POSITIONABLE_HEADER


class Positionable {
  virtual void setX(int newX)=0;
  virtual void setY(int newY)=0;
  virtual int getX()=0;
  virtual int getY()=0;
  virtual void moveX(int newX)=0;
  virtual void moveY(int newY)=0;
  virtual void setSpeed(int newSpeed)=0;
  virtual void boundAtTop(int top, int bottom, int left, int right)=0;
};


#endif
