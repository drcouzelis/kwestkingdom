#ifndef KWESTKINGDOM_HEADER
#define KWESTKINGDOM_HEADER


/**
 * Game specific settings
 */


#define PLAYER_START_ROW (ROWS - 3)
#define PLAYER_START_COL (COLS / 2)


/**
 * The size of a square tile, before being stretched
 */
int grab_tile_size();

/**
 * The default movement speed for all sprites
 */
int grab_walk_speed();

/**
 * Call this anytime to quit the game.
 */
void quit_kwestkingdom();


#endif
