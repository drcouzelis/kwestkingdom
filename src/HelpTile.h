#ifndef HELPTILE_HEADER
#define HELPTILE_HEADER


#include "Drawable.h"
#include "KwestKingdom.h"
#include "Screen.h"
#include "Text.h"


typedef enum {
  UPPER_LEFT,
  UPPER_RIGHT,
  LOWER_LEFT,
  LOWER_RIGHT
} CORNER;


class HelpTile : public Drawable {
  
  int x;
  int y;
  
  char *line1;
  char *line2;
  char *line3;
  char *line4;
  char *line5;
  char *line6;
  
  int location;
  
public:

  HelpTile();
  ~HelpTile();

  void setX(int newX);
  void setY(int newY;)

  void setLine1(char *newLine1,
                char *newLine2,
                char *newLine3,
                char *newLine4,
                char *newLine5,
                char *newLine6);

  void setLocation(int theLocation);

  int getX();
  int getY();


};


#endif
