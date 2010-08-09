#ifndef KK_MESSENGER_H
#define KK_MESSENGER_H


#include <allegro.h>
#include "kk_utilities.h"


#define MESSAGE_LEN 256


typedef struct HELP HELP;
struct ANIM;


struct HELP
{
  char message[MESSAGE_LEN];

  struct ANIM *anim;
  struct ANIM *speaker;
};


MESSENGER *create_messenger(char *message);
MESSENGER *destroy_messenger(MESSENGER *messenger);


#endif

