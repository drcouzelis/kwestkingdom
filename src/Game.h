#ifndef GAME_HEADER
#define GAME_HEADER


#include <allegro.h>
#include "anim.h"
#include "key_input.h"

class Snapshot;
class World;


class Game {
  
  World *world;
  
  int state;
  
  ANIM title_anim;
  ANIM game_over_anim;
  
  KEY_INPUT fullscreenKey;
  KEY_INPUT soundKey;
  KEY_INPUT escapeKey;

  KEY_INPUT upKey;
  KEY_INPUT downKey;
  KEY_INPUT selectKey;
  
  int menuSelection;
  Snapshot *menuBackground;
  Snapshot *highScoresBackground;
  ANIM menu_pointer;

  char playerInitials[4];
  
public:

  Game();
  ~Game();

  virtual void update();
  virtual void draw(BITMAP *buffer);

  void readPlayerInitials();
  bool continuePlaying();
  void activateMenuSelection();
  void drawMenu(BITMAP *buffer);
  void drawHighScores(BITMAP *buffer);
  void drawEnterInitials(BITMAP *buffer);

  void setState(int aState);

  void gameOver();
};


#endif
