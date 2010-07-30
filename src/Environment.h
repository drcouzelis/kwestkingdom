#import <objc/Object.h>


@class Character;


@protocol Environment

- (BOOL)isSwimmableAtX:(int)x y:(int)y;
- (BOOL)isWalkableAtX:(int)x y:(int)y;
- (BOOL)isJumpableAtX:(int)x y:(int)y;
- (BOOL)isFlyableAtX:(int)x y:(int)y;
- (BOOL)isSoarableAtX:(int)x y:(int)y;

- (Character *)player;

- (BOOL) isInhabitedAtX:(int)x y:(int)y;

- (BOOL)isAttackableFromTeam:(int) team x:(int)x y:(int)y;
- attackFromTeam:(int)team x:(int)x y:(int)y;

- shake;

@end
