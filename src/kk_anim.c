#include <malloc.h>

#include "kk_anim.h"
#include "kk_timer.h"




#define KK_ANIM_MAX_FRAMES 16




struct KK_ANIM
{
  BITMAP *frames[KK_ANIM_MAX_FRAMES];
  
  int length;
  int pos;
  bool loop;
  bool done;
  
  int speed;
  int fudge;
  
  bool h_flip;
  bool v_flip;
  bool rotate;
  
  int x_offset;
  int y_offset;
};




//BITMAP * kk_anim_get_canvas(int width, int height);




KK_ANIM * kk_anim_create(int speed, bool loop)
{
  KK_ANIM *anim;
  int i;
  
  anim = malloc(sizeof(*anim));
  
  if (anim) {
    
    for (i = 0; i < KK_ANIM_MAX_FRAMES; i++) {
      anim->frames[i] = NULL;
    }
    
    anim->length = 0;
    anim->pos = 0;
    anim->loop = loop;
    anim->done = false;
    anim->speed = speed;
    anim->fudge = 0;
    anim->h_flip = false;
    anim->v_flip = false;
    anim->rotate = false;
    anim->x_offset = 0;
    anim->y_offset = 0;
  }
  
  return anim;
}




void kk_anim_destroy(KK_ANIM *anim, bool destroy_frames)
{
  int i;
  if (destroy_frames) {
    for (i = 0; i < anim->length; i++) {
      destroy_bitmap(anim->frames[i]);
    }
  }
  free(anim);
}




void kk_anim_add_frame(KK_ANIM *anim, BITMAP *image)
{
  if (image) {
    anim->frames[anim->length] = image;
    anim->length++;
  }
}




void kk_anim_set_offset(KK_ANIM *anim, int x, int y)
{
  if (!anim) {
    return;
  }
  anim->x_offset = x;
  anim->y_offset = y;
}




void kk_anim_transform(KK_ANIM *anim, bool h_flip, bool v_flip, bool rotate)
{
  if (!anim) {
    return;
  }
  anim->h_flip = h_flip;
  anim->v_flip = v_flip;
  anim->rotate = rotate;
}




void kk_anim_animate(KK_ANIM *anim)
{
  if (anim->length > 1 && anim->speed != 0) {
    
    anim->fudge += anim->speed;
    
    while (anim->fudge >= KK_GAME_TICKER) {
      
      anim->pos++;
      
      if (anim->pos == anim->length) {
        if (anim->loop) {
          anim->pos = 0;
        } else {
          anim->pos--;
          anim->done = true;
        }
      }
            
      anim->fudge -= KK_GAME_TICKER;
      
    }
    
  } else {
    
    anim->done = true;
    
  }
}




void kk_anim_reset(KK_ANIM *anim)
{
  anim->pos = 0;
  anim->done = false;
  anim->fudge = 0;
}




KK_ANIM * kk_anim_copy(KK_ANIM *anim, bool deep_frame_copy)
{
  KK_ANIM *new_anim;
  BITMAP *buffer;
  int i;
  
  new_anim = kk_anim_create(anim->speed, anim->loop);
  
  for (i = 0; i < anim->length; i++) {
    if (deep_frame_copy) {
      buffer = create_bitmap(anim->frames[i]->w, anim->frames[i]->h);
      blit(anim->frames[i], buffer, 0, 0, 0, 0, buffer->w, buffer->h);
      kk_anim_add_frame(new_anim, buffer);
    } else {
      kk_anim_add_frame(new_anim, anim->frames[i]);
    }
  }
  
  kk_anim_transform(new_anim, anim->h_flip, anim->v_flip, anim->rotate);
  kk_anim_set_offset(new_anim, anim->x_offset, anim->y_offset);
  
  kk_anim_reset(new_anim);
  
  return new_anim;
}




void kk_anim_draw(KK_ANIM *anim, BITMAP *canvas, int x, int y)
{
  BITMAP *frame; // Points to the current frame
  BITMAP *image; // A temporary drawing area
  
  if (!anim) {
    return;
  }
  
  if (!canvas) {
    return;
  }
  
  frame = anim->frames[anim->pos];
  
  if (!frame) {
    return;
  }
  
  // Write to a temporary canvas to get transparency
  // to work correctly.
  // Only necessary when rotating and flipping sprites.
  /*
  if (anim->rotate || anim->h_flip || anim->v_flip) {
    image = kk_anim_get_canvas(frame->w, frame->h);
    if (image) {
      blit(frame, image, 0, 0, 0, 0, frame->w, frame->h);
    }
  } else {
  */
    image = frame;
  //}
  
  if (!image) {
    return;
  }
  
  x += anim->x_offset;
  y += anim->y_offset;
  
  if (anim->rotate && anim->h_flip && anim->v_flip) {
    rotate_sprite(canvas, image, x, y, itofix(192));
  } else if (anim->rotate && anim->h_flip) {
    rotate_sprite_v_flip(canvas, image, x, y, itofix(192));
  } else if (anim->rotate && anim->v_flip) {
    rotate_sprite_v_flip(canvas, image, x, y, itofix(64));
  } else if (anim->rotate) {
    rotate_sprite(canvas, image, x, y, itofix(64));
  } else if (anim->h_flip && anim->v_flip) {
    rotate_sprite(canvas, image, x, y, itofix(128));
  } else if (anim->h_flip) {
    draw_sprite_h_flip(canvas, image, x, y);
  } else if (anim->v_flip) {
    draw_sprite_v_flip(canvas, image, x, y);
  } else {
    draw_sprite(canvas, image, x, y);
  }
}




/**
 * INTERNAL FUNCTIONS
 */




/*
static BITMAP *canvasStandardSize = NULL;
static BITMAP *canvasTripleSize = NULL;
*/



/**
 * This silly little function provides a fix for transparency
 * when using the rotate sprite and flip sprite functions.
 */
/*
BITMAP * kk_anim_get_canvas(int width, int height)
{
  if (width == kk_tile_size() && height == kk_tile_size()) {
    if (canvasStandardSize == NULL) {
      canvasStandardSize = create_bitmap(kk_tile_size(), kk_tile_size());
    }
    return canvasStandardSize;
  }
  
  if (width == kk_tile_size() * 3 && height == kk_tile_size() * 3) {
    if (canvasTripleSize == NULL) {
      canvasTripleSize = create_bitmap(kk_tile_size() * 3, kk_tile_size() * 3);
    }
    return canvasTripleSize;
  }

  fprintf(stderr, "Failed to find a canvas size %dx%d. \n", width, height);
  
  return NULL;
}
*/
