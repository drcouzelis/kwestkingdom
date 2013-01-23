#include <allegro5/allegro.h>

#include "key_input.h"


/* Hold the state of the keyboard */
static ALLEGRO_KEYBOARD_STATE kbdstate;

static int key_held[ALLEGRO_KEY_MAX] = {0};


int is_key_pressed(char code)
{   
    unsigned int k = code;

    al_get_keyboard_state(&kbdstate);

    if (!key_held[k] && al_key_down(&kbdstate, k)) {
        key_held[k] = 1;
        return 1;
    }

    if (key_held[k] && !al_key_down(&kbdstate, k)) {
        key_held[k] = 0;
        return 0;
    }

    return 0;
}


int is_key_held(char code)
{   
    unsigned int k = code;

    al_get_keyboard_state(&kbdstate);

    if (al_key_down(&kbdstate, k)) {
        key_held[k] = 1;
        return 1;
    }

    key_held[k] = 0;

    return 0;
}
