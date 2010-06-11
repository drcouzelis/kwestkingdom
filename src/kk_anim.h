#ifndef KK_ANIM_H
#define KK_ANIM_H


#include <allegro.h>
#include <stdbool.h>


// An animation represents an animated image.
typedef struct KK_ANIM KK_ANIM;


KK_ANIM * kk_anim_create(int speed, bool loop);

void kk_anim_destroy(KK_ANIM *anim, bool destroy_frames);

// Add a fram to the anim.
void kk_anim_add_frame(KK_ANIM *anim, BITMAP *image);

void kk_anim_set_offset(KK_ANIM *anim, int x, int y);

void kk_anim_transform(KK_ANIM *anim, bool h_flip, bool v_flip, bool rotate);

// Animate the anim. If it is finished
// animating, then nothing will happen.
void kk_anim_animate(KK_ANIM *anim);

// Reset the anim.
void kk_anim_reset(KK_ANIM *anim);

// Copy an anim, including the
// pointers to the frames.
// Returns a pointer to a new anim.
KK_ANIM * kk_anim_copy(KK_ANIM *anim, bool deep_frame_copy);

// Draw the anim onto a canvas.
void kk_anim_draw(KK_ANIM *anim, BITMAP *canvas, int x, int y);


#endif
