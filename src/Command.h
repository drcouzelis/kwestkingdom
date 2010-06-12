#import <objc/Object.h>


@class Condition;


@interface Command : Object {
 @private
  Condition *condition;
}

- execute;


@end

