#ifndef COLLECTABLE_HEADER
#define COLLECTABLE_HEADER


#include "Livable.h"
#include "Moneyable.h"


@protocol Collectable
- collectedBy: (id<Livable, Moneyable>) character;
@end



#endif