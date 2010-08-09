#ifndef KK_SPRITE_H
#define KK_SPRITE_H


#include <allegro.h>


#define MAX_ANIMS 20


typedef struct SPRITE SPRITE;
struct ANIM;


struct SPRITE
{
  /**
   * A collection of animations that represent the
   * sprite on screen.
   */
  ANIM *anims[MAX_ANIMS];
  int num_anims;
  int anim_idx;
  
  /**
   * The position in the room.
   */
  int row;
  int col;
  
  /**
   * The position on the screen.
   */
  int x;
  int y;
  
  /**
   * The size of the character, measured in tiles.
   */
  int w;
  int h;
  
  /**
   * How fast the sprite moves on the screen.
   */
  int speed;
};


/**
 * Animate and move the sprite.
 */
void update_sprite(SPRITE *sprite);

/**
 * Draw the sprite onto a canvas.
 */
void paint_sprite(SPRITE *sprite, BITMAP *canvas);

/**
 * Move the sprite to a new position in the room.
 */
void move_sprite(SPRITE *sprite, int row, int col);

/**
 * Place the sprite instantly at a new position in the room.
 */
void warp_sprite(SPRITE *sprite, int row, int col);


#endif
