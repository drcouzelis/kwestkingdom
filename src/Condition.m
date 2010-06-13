#import "Command.h"
#import "Condition.h"


@implementation Condition


- (BOOL)isMet {
  return NO;
}


- (Command *)nextCommand {
  return nil;
}


@end

