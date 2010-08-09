#include "kk_anim.h"


struct ANIM
{
  /**
   * The collection of images that are part of the animation.
   */
  BITMAP *frames[MAX_FRAMES];
  int length;
  int pos;
  
  /**
   * If loop is true then the animation will loop.
   */
  FLAG loop;
  
  /**
   * This will be true if the animation is finished animating.
   */
  FLAG finished;
  
  /**
   * The speed of the animation.
   */
  int speed;
  
  /**
   * Used internally to make sure the animation is
   * nice and smooth.
   */
  int fudge;
  
  /**
   * Just before the animation is drawn to the screen,
   * the offset is added to its position.
   */
  int x_offset;
  int y_offset;
};
