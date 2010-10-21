#ifndef MESSENGER_HEADER
#define MESSENGER_HEADER


#include <allegro.h>
#include "utilities.h"


#define MESSAGE_LEN 256


typedef struct MESSENGER MESSENGER;
struct ANIM;


struct MESSENGER
{
  char message[MESSAGE_LEN];

  struct ANIM *anim;
  struct ANIM *speaker;
};


MESSENGER *create_messenger(char *message);
MESSENGER *destroy_messenger(MESSENGER *messenger);


#endif

