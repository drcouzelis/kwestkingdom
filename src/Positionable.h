#ifndef POSITIONABLE_HEADER
#define POSITIONABLE_HEADER


@protocol Positionable
- setX: (int) newX;
- setY: (int) newY;
- (int) getX;
- (int) getY;
- moveX: (int) newX;
- moveY: (int) newY;
- setSpeed: (int) newSpeed;
- boundAtTop: (int) top andBottom: (int) bottom andLeft: (int) left andRight: (int) right;
@end



#endif