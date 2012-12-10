#include "HelpTile.h"
#include "KwestKingdom.h"
#include "Screen.h"
#include "Text.h"


HelpTile::HelpTile() {
  x = -1;
  y = -1;
  line1 = NULL;
  line2 = NULL;
  line3 = NULL;
  line4 = NULL;
  line5 = NULL;
  line6 = NULL;
  location = UPPER_LEFT;
}


void HelpTile::draw(BITMAP * buffer) {
  
  int leftSide;
  int upperSide;
  //int numOfLines;
  int lineSpacing;
  //int width;
  //int height;
  
  //numOfLines = 6;
  lineSpacing = 10;
  
  leftSide = 0;
  upperSide = 0;
 
  leftSide = getTileSize(); //(getTileSize() / 2);
  upperSide = (getWindowHeight() / 2) - (getTileSize() * 2); //(getTileSize() / 2);

  //width = getWindowWidth() - (getTileSize() * 2);
  //height = (numOfLines + 2) * lineSpacing;
  
  //drawBox(buffer, leftSide, upperSide, leftSide + width, upperSide + height);
  
  if (line1) {
    resizedTextOut(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 1), 1, WHITE, line1);
  }
  
  if (line2) {
    resizedTextOut(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 2), 1, WHITE, line2);
  }
  
  if (line3) {
    resizedTextOut(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 3), 1, WHITE, line3);
  }
  
  if (line4) {
    resizedTextOut(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 4), 1, WHITE, line4);
  }
  
  if (line5) {
    resizedTextOut(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 5), 1, WHITE, line5);
  }
  
  if (line6) {
    resizedTextOut(buffer, leftSide + lineSpacing, upperSide + (lineSpacing * 6), 1, WHITE, line6);
  }
  
  

  
}


void HelpTile::setX(int newX) {
  x = newX;

}


void HelpTile::setY(int newY) {
  y = newY;

}


void HelpTile::setLines(char *newLine1,
                        char *newLine2,
                        char *newLine3,
                        char *newLine4,
                        char *newLine5,
                        char *newLine6) {
  
  line1 = newLine1;
  line2 = newLine2;
  line3 = newLine3;
  line4 = newLine4;
  line5 = newLine5;
  line6 = newLine6;
}


int HelpTile::getX() {
  return x;
}


int HelpTile::getY() {
  return y;
}


void HelpTile::setLocation(int theLocation) {
  location = theLocation;

}




