#ifndef HELPTILE_HEADER
#define HELPTILE_HEADER


#include <Foundation/Foundation.h>
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


@interface HelpTile : NSObject <Drawable> {
  
  int x;
  int y;
  
  char *line1;
  char *line2;
  char *line3;
  char *line4;
  char *line5;
  char *line6;
  
  int location;
  
}


- setX: (int) newX;
- setY: (int) newY;

- setLine1: (char *) newLine1
      and2: (char *) newLine2
      and3: (char *) newLine3
      and4: (char *) newLine4
      and5: (char *) newLine5
      and6: (char *) newLine6;

- setLocation: (int) theLocation;

- (int) getX;
- (int) getY;


@end


#endif