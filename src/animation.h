#ifndef ANIMATION_H
#define ANIMATION_H


#include <allegro.h>


/**
 * An animation represents an animated image.
 */
typedef struct Animation Animation;


/**
 * Create
 */
Animation *
Animation_create();

/**
 * Destroy
 */
void
Animation_destroy(Animation *animation);

/**
 * Add a fram to the animation.
 */
void
Animation_add_frame(Animation *animation, BITMAP *image);

/**
 * Animate the animation. If it is finished
 * animating, then nothing will happen.
 */
void
Animation_animate(Animation *animation);

/**
 * Reset the animation.
 */
void
Animation_reset(Animation *animation);

/**
 * Copy an animation, including the
 * pointers to the frames.
 *
 * Returns a pointer to a new animation.
 */
Animation *
Animation_copy(Animation *animation);

/**
 * Draw the animation to a bitmap.
 */
void
Animation_draw(Animation *animation, BITMAP *canvas, int x, int y);


#endif
