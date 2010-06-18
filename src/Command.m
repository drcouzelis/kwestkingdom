#import "Command.h"
#import "Condition.h"
#import "List.h"


@implementation Command


- init {
  if ([super init]) {
    conditions = [[List alloc] init];
  }
  return self;
}


- free {
  [conditions freeIncludingItems];
  return [super free];
}


- addCondition:(Condition *)aCondition {
  [conditions add:aCondition];
  return self;
}


- start {
  return self;
}


- execute {
  Iterator *iterator = [[Iterator alloc] initList:conditions];
  while ([iterator hasNext]) {
    Condition *condition = (Condition *)[iterator next];
    [condition check];
  }
  [iterator free];
  return self;
}


- finish {
  return self;
}


- enable {
  enabled = YES;
  return self;
}


- disable {
  enabled = NO;
  return self;
}


@end

