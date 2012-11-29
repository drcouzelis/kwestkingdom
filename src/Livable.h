#ifndef LIVABLE_HEADER
#define LIVABLE_HEADER


#include <Foundation/Foundation.h>


@protocol Livable
- (BOOL) isDead;
- setHealth: (int) theHealth;
- (int) getHealth;
- setMaxHealth: (int) theHealth;
- (int) getMaxHealth;
- hurt;
@end



#endif