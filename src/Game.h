#ifndef GAME_HEADER
#define GAME_HEADER


#include "anim.h"
#include "key_input.h"

class Snapshot;
class World;


class Game {
  
  World *world;
  
  int state;
  
  ANIM title_anim;
  ANIM game_over_anim;
  
  char fullscreenKey;
  char soundKey;
  char escapeKey;

  char upKey;
  char downKey;
  char selectKey;
  char altSelectKey;
  
  int menuSelection;
  Snapshot *menuBackground;
  Snapshot *highScoresBackground;
  ANIM menu_pointer;

  char playerInitials[4];
  
public:

  Game();
  ~Game();

  virtual void update();
  virtual void draw(IMAGE *canvas);

  void readPlayerInitials();
  bool continuePlaying();
  void activateMenuSelection();
  void drawMenu(IMAGE *canvas);
  void drawHighScores(IMAGE *canvas);
  void drawEnterInitials(IMAGE *canvas);

  void setState(int aState);

  void gameOver();
};


#endif
