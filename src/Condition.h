#import <objc/Object.h>


@class Command;


@interface Condition : Object

- (BOOL)isMet;
- (Command *)nextCommand;

@end

