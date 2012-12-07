#ifndef SPRITE_HEADER
#define SPRITE_HEADER


#include <allegro.h>

class World;


class Sprite {
  
protected:

  // Position on the map
  int x; // Horizontal, from 0 to COLS   1
  int y; // Vertical, from 0 to ROWS   1
  int w; // Width of the sprite, or, how many square it occupies horizontally
  int h; // Height of the sprite
  
  // Where the image is on the screen
  int visualX; // Screen width
  int visualY; // Screen height
  int fudge;
  
  int speed; // In FPS
  
  Animation *animation;
  
  World *world;
  
  int state;
  
public:

  Sprite();
  ~Sprite();

  virtual void update();
  virtual void draw(BITMAP *buffer);

  bool moving();
  int getWidth();
  int getHeight();

  void setWorld(World *aWorld);
  void setState(int aState);

  virtual void setX(int newX);
  virtual void setY(int newY);
  virtual int getX();
  virtual int getY();
  virtual void moveX(int newX);
  virtual void moveY(int newY);
  virtual void setSpeed(int newSpeed);
  virtual void bound(int top, int bottom, int left, int right);
};


#endif
