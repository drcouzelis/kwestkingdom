#ifndef DRAWABLE_HEADER
#define DRAWABLE_HEADER


#include <allegro.h>


@protocol Drawable
- (id) draw: (BITMAP *) buffer;
@end



#endif