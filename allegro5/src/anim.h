#ifndef ANIM_HEADER
#define ANIM_HEADER


#include "resources.h"
#include "utilities.h"


#ifdef __cplusplus
  extern "C" {
#endif


#define MAX_FRAMES 16


typedef struct
{
  IMAGE *frames[MAX_FRAMES];
  int len;
  int pos;
  int speed;
  int fudge;
  
  FLAG done;

  // An animation is drawn with respect to its offset.
  int offset_x;
  int offset_y;

  FLAG loop;

  FLAG h_flip;
  FLAG v_flip;
  FLAG rotate;
} ANIM;


void init_anim(ANIM *anim, FLAG loop, int speed);
void copy_anim(ANIM *anim, ANIM *orig);

void animate(ANIM *anim);

IMAGE *get_frame(ANIM *anim);

void add_frame(ANIM *anim, IMAGE *frame);

void reset_anim(ANIM *anim);

void draw_anim(ANIM *anim, IMAGE *canvas, float x, float y);

int get_anim_w(ANIM *anim);
int get_anim_h(ANIM *anim);


#ifdef __cplusplus
  }
#endif


#endif
