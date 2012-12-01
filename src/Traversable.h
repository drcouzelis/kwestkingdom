#ifndef TRAVERSABLE_HEADER
#define TRAVERSABLE_HEADER


#include <Foundation/Foundation.h>


@protocol Traversable
- (bool) isSwimmableAtX: (int) x andY: (int) y;
- (bool) isWalkableAtX: (int) x andY: (int) y;
- (bool) isJumpableAtX: (int) x andY: (int) y;
- (bool) isFlyableAtX: (int) x andY: (int) y;
- (bool) isSoarableAtX: (int) x andY: (int) y;
@end



#endif