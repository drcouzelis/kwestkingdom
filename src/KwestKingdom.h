#ifndef KWESTKINGDOM_HEADER
#define KWESTKINGDOM_HEADER


#include <allegro.h>


#define GAME_TICKER 100


// Colors
#define WHITE (makecol(255, 255, 255)) //2
#define BLACK (makecol(0, 0, 0)) //1
#define GREEN (makecol(0, 255, 0))
#define BLUE (makecol(0, 0, 100))
#define LIGHT_BLUE (makecol(130, 229, 255))
#define RED (makecol(109, 4, 4))
#define GRAY (makecol(109, 109, 109))
#define MAGICPINK (makecol(255, 0, 255))

#define TILE_SIZE 20

#define COLS 16
#define ROWS 12

#define WINDOW_WIDTH (COLS * TILE_SIZE)
#define WINDOW_HEIGHT (ROWS * TILE_SIZE)

#define DEFAULT_SCREEN_RATIO 2


int getTileSize();
int getWalkSpeed();

void game_over();


#endif
