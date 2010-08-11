#ifndef ANIM_HEADER
#define ANIM_HEADER


#include <allegro.h>
#include "utilities.h"


typedef struct ANIM ANIM;


ANIM *create_anim(int speed, FLAG loop);
void destroy_anim(ANIM *anim);

/**
 * Add a frame to an animation.
 */
void add_frame(ANIM *anim, BITMAP *frame);

/**
 * Set the visual offset of an animation.
 */
void set_visual_offset(ANIM *anim, int x_offset, int y_offset);

/**
 * Animate an animation.
 * If this is a non-looping animation and it is already
 * at the last frame, then nothing will happen.
 */
void animate(ANIM *anim);

/**
 * An animation is finished if it is completely done
 * showing its last frame.
 * A looping animation will never finish.
 */
FLAG is_done_animating(ANIM *anim);

int anim_width(ANIM *anim);
int anim_height(ANIM *anim);

/**
 * Reset an animation to its first frame.
 */
void reset_anim(ANIM *anim);

/**
 * Copy an animation.
 * Returns a pointer to a new animation.
 */
ANIM *copy_anim(ANIM *anim);

/**
 * Draw an animation.
 * It will be drawn to the given position, plus
 * the offsets.
 */
void paint_anim(ANIM *anim, BITMAP *canvas, int x, int y);


#endif
