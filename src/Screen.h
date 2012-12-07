#ifndef SCREEN_HEADER
#define SCREEN_HEADER


#include <allegro.h>


void setWindowSize(int width, int height);

bool initializeScreen(int width, int height, bool fullscreen);
void destroyScreen();

int getWindowWidth();
int getWindowHeight();

BITMAP *getWindow();
bool showScreen();


#endif
