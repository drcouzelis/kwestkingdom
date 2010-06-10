#ifndef KK_TIMER_H
#define KK_TIMER_H


#define KK_GAME_TICKER 100


void KK_init_timer();
void KK_reset_timer();

inline int KK_ticks();

inline void KK_decrease_timer();

inline void KK_update_fps();
inline int KK_get_fps();


#endif

