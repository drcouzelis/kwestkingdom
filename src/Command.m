#import "Command.h"
#import "Condition.h"
#import "List.h"


@implementation Command


- init {
  if ([super init]) {
    conditions = [[[List alloc] init] ownsItems:YES];
  }
  return self;
}


- free {
  [conditions free];
  return [super free];
}


- addCondition:(Condition *)aCondition {
  [conditions push:aCondition];
  return self;
}


- start {
  return self;
}


- execute {
  [conditions iterate];
  while ([conditions hasNext]) {
    Condition *condition = (Condition *)[conditions next];
    [condition check];
  }
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

