#ifndef TEXT_HEADER
#define TEXT_HEADER


#include "resources.h"


#ifdef __cplusplus
    extern "C" {
#endif 


void draw_text(float x, float y, char *text);
void draw_box(float x, float y, int w, int h);


#ifdef __cplusplus
    }
#endif 

#endif
