#ifndef SCREEN_HEADER
#define SCREEN_HEADER

#ifdef __cplusplus
    extern "C" {
#endif 


#include "utilities.h"


FLAG init_screen(int width, int height, int fullscreen);
void free_screen();

FLAG show_screen();


#ifdef __cplusplus
    }
#endif 

#endif
