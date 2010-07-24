#import <objc/Object.h>
#import <allegro.h>
#import "al_screen.h"
#import "KwestKingdom.h"


void setWindowSize(int width, int height);

BOOL initializeScreen(int width, int height, BOOL fullscreen);
void destroyScreen();

int getWindowWidth();
int getWindowHeight();

BITMAP *getWindow();
BOOL showScreen();

