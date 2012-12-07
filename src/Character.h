#ifndef CHARACTER_HEADER
#define CHARACTER_HEADER


#include "Sprite.h"


typedef enum {
  NO_TEAM,
  HERO_TEAM,
  ENEMY_TEAM
} TEAM;


class Character : public Sprite {
  
protected:

  int health;
  int maxHealth;
  int money;
  int team; // Characters on the same team can't hurt each other.
  
  int turns;
  
public:

  Character();

  virtual bool isDead();
  virtual void setHealth(int theHealth);
  virtual int getHealth();
  virtual void setMaxHealth(int theHealth);
  virtual int getMaxHealth();
  virtual void hurt();

  virtual int getMoney();
  virtual void setMoney(int amount);

  bool waiting();
  void wait();
  void go();

  void setTeam(int aTeam);
  int getTeam();
};


#endif
