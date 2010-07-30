#import "Condition.h"
#import "State.h"


@implementation State


- free {
  int i;
  for (i = 0; i < numConditions; i++) {
    [conditions[i] free];
  }
  return [super free];
}


- addCondition:(Condition *)condition {
  if (numConditions < MAX_CONDITIONS) {
    conditions[numConditions] = condition;
    numConditions++;
  } else {
    fprintf(stderr, "Failed to add condition because there are too many. \n");
  }
  return self;
}


- start {
  return self;
}


- update {
  int i;
  for (i = 0; i < numConditions; i++) {
    [conditions[i] check];
  }
  return self;
}


- finish {
  return self;
}


@end

