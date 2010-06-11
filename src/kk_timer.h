#ifndef KK_TIMER_H
#define KK_TIMER_H


#define KK_GAME_TICKER 100


void kk_init_timer();
void kk_reset_timer();

inline int kk_ticks();

inline void kk_decrease_timer();

inline int kk_get_fps();
inline void kk_frame_complete();


#endif

