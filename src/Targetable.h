#ifndef TARGETABLE_HEADER
#define TARGETABLE_HEADER


#include "Positionable.h"


@protocol Targetable
- (id<Positionable>) getTarget;
@end



#endif