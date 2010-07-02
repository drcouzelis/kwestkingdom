#import <objc/Object.h>


@class Character;


@interface EnemyFactory : Object
+ (Character2 *)createChomperX:(int)x y:(int)y;
@end
