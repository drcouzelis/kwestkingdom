#ifndef HELPTILE_HEADER
#define HELPTILE_HEADER


#include "resources.h"


typedef enum {
  UPPER_LEFT,
  UPPER_RIGHT,
  LOWER_LEFT,
  LOWER_RIGHT
} CORNER;


class HelpTile {
  
protected:

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

  virtual void draw(IMAGE *canvas);

  void setX(int newX);
  void setY(int newY);

  void setLines(char *newLine1,
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
