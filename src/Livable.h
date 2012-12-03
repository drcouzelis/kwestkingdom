#ifndef LIVABLE_HEADER
#define LIVABLE_HEADER


class Livable {
  virtual bool isDead=0;
  virtual void setHealth(int theHealth)=0;
  virtual int getHealth()=0;
  virtual void setMaxHealth(int theHealth)=0;
  virtual int getMaxHealth()=0;
  virtual void hurt()=0;
};


#endif
