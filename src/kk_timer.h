#ifndef KK_TIMER_H
#define KK_TIMER_H


#define GAME_TICKER 100


void init_timer();

/**
 * Reset the game ticker to zero.
 */
void reset_timer();

/**
 * Get the number of game ticks since the last update.
 */
int get_ticks();

void decrease_timer();

int get_fps();

/**
 * Call this function when the game is done updating one frame.
 */
void mark_frame_complete();


#endif

