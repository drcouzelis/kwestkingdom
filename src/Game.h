#ifndef GAME_HEADER
#define GAME_HEADER


#include <allegro.h>

class Animation;
class KeyControl;
class Snapshot;
class World;


class Game {
  
  World *world;
  
  int state;
  
  Animation *titleAnimation;
  Animation *gameOverAnimation;
  
  KeyControl *fullscreenKey;
  KeyControl *soundKey;
  KeyControl *escapeKey;
  
  KeyControl *upKey;
  KeyControl *downKey;
  KeyControl *selectKey;
  
  int menuSelection;
  Snapshot *menuBackground;
  Snapshot *highScoresBackground;
  Animation *menuPointer;
  
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
