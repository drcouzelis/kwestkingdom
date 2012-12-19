#ifndef HIGHSCORELIBRARY_HEADER
#define HIGHSCORELIBRARY_HEADER

#ifdef __cplusplus
    extern "C" {
#endif 


#include "utilities.h"


#define MAX_NUM_OF_HIGH_SCORES 5


typedef struct
{
  char initials[4];
  int room;
  int money;
} HIGH_SCORE;


int high_score_pos(int room, int money);
void add_high_score(char *initials, int room, int money);
FLAG get_high_score(int num, HIGH_SCORE *high_score);


#ifdef __cplusplus
    }
#endif 

#endif
