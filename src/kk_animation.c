#include <malloc.h>
#include <stdio.h>

#include "kk_animation.h"
#include "kk_kwestkingdom.h"
#include "kk_timer.h"
#include "kk_utilities.h"




#define KK_ANIMATION_MAX_FRAMES 16




struct KK_Animation
{
  BITMAP *frames[KK_ANIMATION_MAX_FRAMES];
  
  int length;
  int pos;
  FLAG loop;
  FLAG finished;
  
  int speed;
  int fudge;
  
  FLAG h_flip;
  FLAG v_flip;
  FLAG rotate;
  
  int x_offset;
  int y_offset;
};




BITMAP * KK_Animation_get_canvas(int width, int height);




KK_Animation * KK_Animation_create()
{
  KK_Animation *animation;
  int i;
  
  animation = malloc(sizeof(*animation));
  
  if (animation) {
    
    for (i = 0; i < KK_ANIMATION_MAX_FRAMES; i++) {
      animation->frames[i] = NULL;
    }
    
    animation->length = 0;
    animation->pos = 0;
    animation->loop = OFF;
    animation->finished = ON;
    animation->speed = 0;
    animation->fudge = 0;
    animation->h_flip = OFF;
    animation->v_flip = OFF;
    animation->rotate = OFF;
    animation->x_offset = 0;
    animation->y_offset = 0;
  }
  
  return animation;
}




void KK_Animation_destroy(KK_Animation *animation)
{
  free(animation);
}




void KK_Animation_add_frame(KK_Animation *animation, BITMAP *image)
{
  if (image) {
    animation->frames[animation->length] = image;
    animation->length++;
  }
}




void KK_Animation_animate(KK_Animation *animation)
{
  if (animation->length > 1 && animation->speed != 0) {
    
    animation->fudge += animation->speed;
    
    while (animation->fudge >= KK_GAME_TICKER) {
      
      animation->pos++;
      
      if (animation->pos == animation->length) {
        if (animation->loop) {
          animation->pos = 0;
        } else {
          animation->pos--;
          animation->finished = ON;
        }
      }
            
      animation->fudge -= KK_GAME_TICKER;
      
    }
    
  } else {
    
    animation->finished = ON;
    
  }
}




void KK_Animation_reset(KK_Animation *animation)
{
  animation->pos = 0;
  animation->finished = OFF;
  animation->fudge = 0;
}




KK_Animation * KK_Animation_copy(KK_Animation *animation)
{
  KK_Animation *new_anim;
  int i;
  
  new_anim = KK_Animation_create();
  
  for (i = 0; i < animation->length; i++) {
    KK_Animation_add_frame(new_anim, animation->frames[i]);
  }
  
  new_anim->loop = animation->loop;
  new_anim->speed = animation->speed;
  new_anim->h_flip = animation->h_flip;
  new_anim->v_flip = animation->v_flip;
  new_anim->rotate = animation->rotate;
  new_anim->x_offset = animation->x_offset;
  new_anim->y_offset = animation->y_offset;
  
  KK_Animation_reset(new_anim);
  
  return new_anim;
}




void KK_Animation_draw(KK_Animation *animation, BITMAP *canvas, int x, int y)
{
  BITMAP *frame; // Points to the current frame
  BITMAP *image; // A temporary drawing area
  
  if (!animation) {
    return;
  }
  
  if (!canvas) {
    return;
  }
  
  frame = animation->frames[animation->pos];
  
  if (!frame) {
    return;
  }
  
  // Write to a temporary canvas to get transparency
  // to work correctly.
  // Only necessary when rotating and flipping sprites.
  if (animation->rotate || animation->h_flip || animation->v_flip) {
    image = KK_Animation_get_canvas(frame->w, frame->h);
    if (image) {
      blit(frame, image, 0, 0, 0, 0, frame->w, frame->h);
    }
  } else {
    image = frame;
  }
  
  if (!image) {
    return;
  }
  
  x += animation->x_offset;
  y += animation->y_offset;
  
  if (animation->rotate && animation->h_flip && animation->v_flip) {
    rotate_sprite(canvas, image, x, y, itofix(192));
  } else if (animation->rotate && animation->h_flip) {
    rotate_sprite_v_flip(canvas, image, x, y, itofix(192));
  } else if (animation->rotate && animation->v_flip) {
    rotate_sprite_v_flip(canvas, image, x, y, itofix(64));
  } else if (animation->rotate) {
    rotate_sprite(canvas, image, x, y, itofix(64));
  } else if (animation->h_flip && animation->v_flip) {
    rotate_sprite(canvas, image, x, y, itofix(128));
  } else if (animation->h_flip) {
    draw_sprite_h_flip(canvas, image, x, y);
  } else if (animation->v_flip) {
    draw_sprite_v_flip(canvas, image, x, y);
  } else {
    draw_sprite(canvas, image, x, y);
  }
}




/**
 * INTERNAL FUNCTIONS
 */




static BITMAP *canvasStandardSize = NULL;
static BITMAP *canvasTripleSize = NULL;




/**
 * This silly little function provides a fix for transparency
 * when using the rotate sprite and flip sprite functions.
 */
BITMAP * KK_Animation_get_canvas(int width, int height)
{
  if (width == KK_tile_size() && height == KK_tile_size()) {
    if (canvasStandardSize == NULL) {
      canvasStandardSize = create_bitmap(KK_tile_size(), KK_tile_size());
    }
    return canvasStandardSize;
  }
  
  if (width == KK_tile_size() * 3 && height == KK_tile_size() * 3) {
    if (canvasTripleSize == NULL) {
      canvasTripleSize = create_bitmap(KK_tile_size() * 3, KK_tile_size() * 3);
    }
    return canvasTripleSize;
  }

  fprintf(stderr, "Failed to find a canvas size %dx%d. \n", width, height);
  
  return NULL;
}

