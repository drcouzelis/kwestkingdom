#ifndef KK_INPUT_H
#define KK_INPUT_H


#include <stdbool.h>


typedef struct KK_KEY KK_KEY;


/**
 * If repeat is false, the key will only be "pressed"
 * once until you release it and press it again.
 */
KK_KEY * kk_key_create(int keycode, bool repeat);

void kk_key_destroy(KK_KEY *k);

bool kk_key_is_pressed(KK_KEY *k);


#endif
