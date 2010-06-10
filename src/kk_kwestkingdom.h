#ifndef KK_KWESTKINGDOM_H
#define KK_KWESTKINGDOM_H


#define KK_TILE_SIZE 20

#define KK_COLS 16
#define KK_ROWS 12

#define KK_WINDOW_WIDTH (KK_COLS * KK_TILE_SIZE)
#define KK_WINDOW_HEIGHT (KK_ROWS * KK_TILE_SIZE)

#define KK_DEFAULT_SCREEN_RATIO 2


int KK_tile_size();
int KK_walk_speed();

void KKquit_game();


#endif

