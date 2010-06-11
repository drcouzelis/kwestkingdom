#ifndef KK_UTILITIES_H
#define KK_UTILITIES_H


typedef enum KK_DIRECTION KK_DIRECTION;


enum KK_DIRECTION {
  KK_U,
  KK_D,
  KK_L,
  KK_R
};


int kk_random_number(int low, int high);


#endif
