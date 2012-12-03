#ifndef INHABITABLE_HEADER
#define INHABITABLE_HEADER


#include "Character.h"
#include "Item.h"


class Inhabitable {
  virtual bool isInhabited(int x, int y)=0;

  virtual bool isAttackable(int team, int x, int y)=0;
  virtual void attackFromTeam(int team, int x, int y)=0;
  virtual void shake()=0;

  virtual void addCharacter(Character *aCharacter)=0;
  virtual void addItem(Item  *anItem)=0;
};


#endif
