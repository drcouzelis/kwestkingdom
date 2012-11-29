#import <Foundation/Foundation.h>


@protocol Livable
- (BOOL) isDead;
- setHealth: (int) theHealth;
- (int) getHealth;
- setMaxHealth: (int) theHealth;
- (int) getMaxHealth;
- hurt;
@end

