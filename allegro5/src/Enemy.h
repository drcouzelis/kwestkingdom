#ifndef ENEMY_HEADER
#define ENEMY_HEADER


#include "Character.h"


#define MAX_ENEMY_HEALTH 3


class Enemy : public Character {

public:

  Enemy();

  virtual void dropItem();
};


#endif
