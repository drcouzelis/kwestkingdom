#ifndef KWESTKINGDOM_H
#define KWESTKINGDOM_H


#define TILE_SIZE 20

#define COLS 16
#define ROWS 12

#define WINDOW_WIDTH (COLS * TILE_SIZE)
#define WINDOW_HEIGHT (ROWS * TILE_SIZE)

#define DEFAULT_SCREEN_RATIO 2


int tile_size();
int walk_speed();

void game_over();


#endif

