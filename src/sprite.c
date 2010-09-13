#include "anim.h"
#include "kwestkingdom.h"
#include "sprite.h"
#include "timer.h"




SPRITE *create_sprite()
{
  SPRITE *sprite;
  int i;
  
  sprite = malloc(sizeof(SPRITE));
  
  for (i = 0; i < MAX_ANIMS; i++) {
    sprite->anims[i] = NULL;
  }
  
  sprite->num_anims = 0;
  sprite->anim_idx = 0;
  
  sprite->row = 0;
  sprite->col = 0;
  sprite->x = 0;
  sprite->y = 0;
  sprite->w = 1;
  sprite->h = 1;
  
  sprite->speed = 20;
  sprite->fudge = 0;
  
  return sprite;
}




void destroy_sprite(SPRITE *sprite)
{
  int i;
  
  if (sprite == NULL) {
    return;
  }
  
  for (i = 0; i < sprite->num_anims; i++) {
    destroy_anim(sprite->anims[i]);
  }
  
  free(sprite->anims);
  
  free(sprite);
}




void add_animation(SPRITE *sprite, struct ANIM *anim)
{
  sprite->anims[sprite->num_anims] = anim;
  sprite->num_anims++;
}




void update_sprite(SPRITE *sprite)
{
  animate(sprite->anims[sprite->anim_idx]);
  
  /**
   * This will make the visual position of the sprite match up
   * with the actual position of the sprite at the right speed.
   */
  if (is_moving(sprite)) {
    
    if (sprite->speed > 0) {
      
      sprite->fudge += sprite->speed;
      
      while (sprite->fudge >= GAME_TICKER) {
        
        if (sprite->x != sprite->col * get_tile_size()) {
          if (sprite->x < sprite->col * get_tile_size()) {
            sprite->x++;
          } else {
            sprite->x--;
          }
        }
        
        if (sprite->y != sprite->row * get_tile_size()) {
          if (sprite->y < sprite->row * get_tile_size()) {
            sprite->y++;
          } else {
            sprite->y--;
          }
        }
        
        sprite->fudge -= GAME_TICKER;
      }
      
    } else {
      sprite->x = sprite->col * get_tile_size();
      sprite->y = sprite->row * get_tile_size();
    }
    
    /**
     * If the sprite isn't moving, reset the fudge.
     */
    if (!is_moving(sprite)) {
      sprite->fudge = 0;
    }
  }
}




void paint_sprite(SPRITE *sprite, BITMAP *canvas)
{
  paint_anim(sprite->anims[sprite->anim_idx], canvas, sprite->x, sprite->y);
}




void move_sprite(SPRITE *sprite, int row, int col)
{
  sprite->row = row;
  sprite->col = col;
}




void warp_sprite(SPRITE *sprite, int row, int col)
{
  sprite->row = row;
  sprite->col = col;
  sprite->x = col * get_tile_size();
  sprite->y = row * get_tile_size();
}




FLAG is_moving(SPRITE *sprite)
{
  if (sprite->x != sprite->col * get_tile_size() || sprite->y != sprite->row * get_tile_size()) {
    return ON;
  }
  
  return OFF;
}

