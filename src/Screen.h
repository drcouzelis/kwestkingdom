#ifndef SCREEN_HEADER
#define SCREEN_HEADER


#include <Foundation/Foundation.h>
#include <allegro.h>
#include "al_screen.h"
#include "KwestKingdom.h"


void setWindowSize(int width, int height);

BOOL initializeScreen(int width, int height, BOOL fullscreen);
void destroyScreen();

int getWindowWidth();
int getWindowHeight();

BITMAP *getWindow();
BOOL showScreen();



#endif