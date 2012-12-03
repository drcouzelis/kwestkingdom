#ifndef TRAVERSABLE_HEADER
#define TRAVERSABLE_HEADER


class Traversable {
  virtual bool isSwimmable(int x, int y);
  virtual bool isWalkable(int x, int y);
  virtual bool isJumpable(int x, int y);
  virtual bool isFlyable(int x, int y);
  virtual bool isSoarable(int x, int y);
};


#endif
