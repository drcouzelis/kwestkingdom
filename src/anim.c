#include <stdio.h>
#include "anim.h"
#include "KwestKingdom.h"


extern int timer;


void init_anim(ANIM *anim)
{
  int i;
  
  for (i = 0; i < MAX_FRAMES; i++) {
    anim->frames[i] = NULL;
  }
  
  anim->len = 0;
  anim->pos = 0;
  anim->loop = ON;
  anim->done = OFF;
  anim->speed = 0;
  anim->fudge = 0;
  anim->offset_x = 0;
  anim->offset_y = 0;
  anim->h_flip = OFF;
  anim->v_flip = OFF;
  anim->rotate = OFF;
}


void copy_anim(ANIM *anim, ANIM *orig)
{
  int i;

  init_anim(anim);
  
  for (i = 0; i < orig->len; i++) {
    add_frame(anim, orig->frames[i]);
  }
  
  anim->offset_x = orig->offset_x;
  anim->offset_y = orig->offset_y;
  anim->loop = orig->loop;
  anim->speed = orig->speed;
  anim->h_flip = orig->h_flip;
  anim->v_flip = orig->v_flip;
  anim->rotate = orig->rotate;

  reset_anim(anim);
}


void reset_anim(ANIM *anim)
{
  anim->pos = 0;
  anim->done = OFF;
  anim->fudge = 0;
}


IMAGE *get_frame(ANIM *anim)
{
  if (anim->len == 0) {
    return NULL;
  }
  return anim->frames[anim->pos];
}


void add_frame(ANIM *anim, IMAGE *frame)
{
  if (frame) {
    anim->frames[anim->len] = frame;
    anim->len++;
  }
}


static IMAGE *canvas_standard_size = NULL;
static IMAGE *canvas_triple_size = NULL;


/**
 * This silly little function provides a fix for transparency
 * when using the rotate sprite and flip sprite functions.
 */
IMAGE *get_canvas(int width, int height)
{
  int tile_size = 20;
  
  if (width == tile_size && height == tile_size) {
    if (canvas_standard_size == NULL) {
      canvas_standard_size = create_bitmap(tile_size, tile_size);
    }
    return canvas_standard_size;
  }
  
  if (width == tile_size * 3 && height == tile_size * 3) {
    if (canvas_triple_size == NULL) {
      canvas_triple_size = create_bitmap(tile_size * 3, tile_size * 3);
    }
    return canvas_triple_size;
  }

  fprintf(stderr, "Failed to find a canvas size %dx%d. \n", width, height);
  
  return NULL;
}


#include <stdio.h>


void draw_anim(ANIM *anim, IMAGE *buffer, int x, int y)
{
  IMAGE *canvas;

  if (get_frame(anim) == NULL) {
    return;
  }
  
  // Write to a temporary canvas to get transparency
  // to work correctly.
  // Only necessary when rotating and flipping sprites.
  if (anim->rotate || anim->h_flip || anim->v_flip) {
    canvas = get_canvas(get_frame(anim)->w, get_frame(anim)->h);
    if (canvas) {
      blit(get_frame(anim), canvas, 0, 0, 0, 0, canvas->w, canvas->h);
    }
  } else {
    canvas = get_frame(anim);
  }
  
  if (canvas == NULL) {
    return;
  }
  
  if (anim->rotate && anim->h_flip && anim->v_flip) {
    rotate_sprite(buffer, canvas, x + anim->offset_x, y + anim->offset_y, itofix(192));
  } else if (anim->rotate && anim->h_flip) {
    rotate_sprite_v_flip(buffer, canvas, x + anim->offset_x, y + anim->offset_y, itofix(192));
  } else if (anim->rotate && anim->v_flip) {
    rotate_sprite_v_flip(buffer, canvas, x + anim->offset_x, y + anim->offset_y, itofix(64));
  } else if (anim->rotate) {
    rotate_sprite(buffer, canvas, x + anim->offset_x, y + anim->offset_y, itofix(64));
  } else if (anim->h_flip && anim->v_flip) {
    rotate_sprite(buffer, canvas, x + anim->offset_x, y + anim->offset_y, itofix(128));
  } else if (anim->h_flip) {
    draw_sprite_h_flip(buffer, canvas, x + anim->offset_x, y + anim->offset_y);
  } else if (anim->v_flip) {
    draw_sprite_v_flip(buffer, canvas, x + anim->offset_x, y + anim->offset_y);
  } else {
    draw_sprite(buffer, canvas, x + anim->offset_x, y + anim->offset_y);
  }
}


// Animate the animation.
void animate(ANIM *anim) {
  
  if (anim->len > 1 && anim->speed != 0) {
    
    anim->fudge += anim->speed;
    
    while (anim->fudge >= GAME_TICKER) {
      
      anim->pos++;
      
      if (anim->pos == anim->len) {
        if (anim->loop) {
          anim->pos = 0;
        } else {
          anim->pos--;
          anim->done = ON;
        }
      }
            
      anim->fudge -= GAME_TICKER;
      
    }
    
  } else {
    
    anim->done = ON;
    
  }
}


int get_anim_w(ANIM *anim)
{
  if (get_frame(anim)) {
    return get_frame(anim)->w;
  }
  return 0;
}


int get_anim_h(ANIM *anim)
{
  if (get_frame(anim)) {
    return get_frame(anim)->h;
  }
  return 0;
}

