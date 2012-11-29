#ifndef INHABITABLE_HEADER
#define INHABITABLE_HEADER


#include <Foundation/Foundation.h>


@protocol Inhabitable

- (BOOL) isInhabitedAtX: (int) x andY: (int) y;

- (BOOL) isAttackableFromTeam: (int) team atX: (int) x andY: (int) y;
- attackFromTeam: (int) team atX: (int) x andY: (int) y;
- shake;

- addCharacter: (id) aCharacter;
- addItem: (id) anItem;

@end



#endif