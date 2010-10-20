#include "anim.h"
#include "memory.h"
#include "timer.h"




/**
 * Private
 */




#define MAX_FRAMES 20




struct ANIM
{
  /**
   * The collection of images that are part of the animation.
   */
  BITMAP *frames[MAX_FRAMES];
  int length;
  int pos;

  /**
   * If loop is true then the animation will loop.
   */
  FLAG loop;

  /**
   * This will be true if the animation is finished animating.
   */
  FLAG finished;

  /**
   * The speed of the animation.
   */
  int speed;

  /**
   * Used internally to make sure the animation is
   * nice and smooth.
   */
  int fudge;

  /**
   * Just before the animation is drawn to the screen,
   * the offset is added to its position.
   */
  int x_offset;
  int y_offset;
};




/**
 * Public
 */




ANIM *create_anim(int speed, FLAG loop)
{
  ANIM *anim;
  int i;

  anim = alloc_memory(sizeof(ANIM));

  for (i = 0; i < MAX_FRAMES; i++) {
    anim->frames[i] = NULL;
  }

  anim->length = 0;
  anim->pos = 0;
  anim->loop = loop;
  anim->finished = OFF;
  anim->speed = speed;
  anim->fudge = 0;
  anim->x_offset = 0;
  anim->y_offset = 0;

  return anim;
}




void destroy_anim(ANIM *anim)
{
  free_memory(anim);
}




void add_frame(ANIM *anim, BITMAP *image)
{
  if (anim == NULL) {
    return;
  }
  if (image) {
    anim->frames[anim->length] = image;
    anim->length++;
  }
}




void change_visual_offset(ANIM *anim, int x_offset, int y_offset)
{
  if (anim == NULL) {
    return;
  }
  anim->x_offset = x_offset;
  anim->y_offset = y_offset;
}




void animate(ANIM *anim)
{
  if (anim == NULL) {
    return;
  }

  if (anim->length > 1 && anim->speed != 0) {

    anim->fudge += anim->speed;

    while (anim->fudge >= GAME_TICKER) {

      anim->pos++;

      if (anim->pos == anim->length) {
        if (anim->loop) {
          anim->pos = 0;
        } else {
          anim->pos--;
          anim->finished = ON;
        }
      }

      anim->fudge -= GAME_TICKER;
    }

  } else {

    anim->finished = ON;

  }
}




FLAG is_done_animating(ANIM *anim)
{
  if (anim == NULL) {
    return ON;
  }
  return anim->finished;
}




int grab_anim_width(ANIM *anim)
{
  if (anim == NULL) {
    return 0;
  }
  return anim->frames[anim->pos]->w;
}




int grab_anim_height(ANIM *anim)
{
  if (anim == NULL) {
    return 0;
  }
  return anim->frames[anim->pos]->h;
}




void reset_anim(ANIM *anim)
{
  if (anim == NULL) {
    return;
  }
  anim->pos = 0;
  anim->finished = OFF;
  anim->fudge = 0;
}




void paint_anim(ANIM *anim, BITMAP *canvas, int x, int y)
{
  if (anim == NULL || canvas == NULL) {
    return;
  }

  x += anim->x_offset;
  y += anim->y_offset;

  draw_sprite(canvas, anim->frames[anim->pos], x, y);
}
