#ifndef KK_ANIM_H
#define KK_ANIM_H


#include <allegro.h>
#include "kk_utilities.h"


#define MAX_FRAMES 20


typedef struct ANIM ANIM;


ANIM * create_anim(void);
ANIM * destroy_anim(ANIM *anim);

/**
 * Add a frame to an animation.
 */
void add_frame(BITMAP *frame, ANIM *anim);

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

/**
 * Reset an animation to its first frame.
 */
void reset_anim(ANIM *anim);

/**
 * Draw an animation.
 * It will be drawn to the given position, plus
 * the offsets.
 */
void paint_anim(ANIM *anim, BITMAP *canvas, int x, int y);


#endif
