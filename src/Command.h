#import <objc/Object.h>


@class Condition;
@class List;


@interface Command : Object {
 @private
  List *conditions;
  BOOL enabled;
}

- addCondition:(Condition *)aCondition;

- start;
- execute;
- finish;

- enable;
- disable;

@end

