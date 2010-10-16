#ifndef KWESTKINGDOM_HEADER
#define KWESTKINGDOM_HEADER


#define PLAYER_START_ROW (ROWS - 3)
#define PLAYER_START_COL (COLS / 2)


int get_tile_size();
int get_walk_speed();

/**
 * Call this anytime to quit the game.
 */
void quit_kwestkingdom();


#endif
