#ifndef KK_ANIMATION_H
#define KK_ANIMATION_H


#include <allegro.h>


/**
 * An animation represents an animated image.
 */
typedef struct KK_Animation KK_Animation;


/**
 * Create
 */
KK_Animation * KK_Animation_create();

/**
 * Destroy
 */
void KK_Animation_destroy(KK_Animation *animation);

/**
 * Add a fram to the animation.
 */
void KK_Animation_add_frame(KK_Animation *animation, BITMAP *image);

/**
 * Animate the animation. If it is finished
 * animating, then nothing will happen.
 */
void KK_Animation_animate(KK_Animation *animation);

/**
 * Reset the animation.
 */
void KK_Animation_reset(KK_Animation *animation);

/**
 * Copy an animation, including the
 * pointers to the frames.
 *
 * Returns a pointer to a new animation.
 */
KK_Animation * KK_Animation_copy(KK_Animation *animation);

/**
 * Draw the animation to a bitmap.
 */
void KK_Animation_draw(KK_Animation *animation, BITMAP *canvas, int x, int y);


#endif
