#import "Livable.h"
#import "Moneyable.h"


@protocol Collectable
- collectedBy: (id<Livable, Moneyable>) character;
@end

