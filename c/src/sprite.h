#ifndef SPRITE_HEADER
#define SPRITE_HEADER


#include <allegro.h>

#include "utilities.h"


#define MAX_ANIMS 20


typedef struct SPRITE SPRITE;
struct ANIM;


struct SPRITE
{
  /**
   * A collection of animations that represent the
   * sprite on screen.
   */
  struct ANIM *anims[MAX_ANIMS];
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
  int fudge;
};


SPRITE *create_sprite();
void destroy_sprite(SPRITE *sprite);

/**
 * Add animation at "index", which could be a named enum.
 * If index is -1, then the animation will be added in the
 * next available empty space.
 */
void add_anim(SPRITE *sprite, struct ANIM *anim, int index);

/**
 * Change the current animation to the one at the index.
 */
void change_anim(SPRITE *sprite, int index);

/**
 * Retrieve the animation at the index.
 * Use the special index of "CURRENT_ANIM" to get
 * the current animation.
 */
#define CURRENT_ANIM -1

struct ANIM *grab_anim(SPRITE *sprite, int index);

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

/**
 * Returns true if the sprite is currently moving.
 */
FLAG is_moving(SPRITE *sprite);

/**
 * The default movement speed for all sprites
 */
int grab_walk_speed();


#endif
