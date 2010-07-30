#import <objc/Object.h>


#define MAX_CONDITIONS 8


@class Condition;


@interface State : Object {
 @private
  Condition *conditions[MAX_CONDITIONS];
  int numConditions;
}

- addCondition:(Condition *)condition;

- start;
- update;
- finish;

@end
