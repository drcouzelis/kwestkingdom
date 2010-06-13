#import <objc/Object.h>


@class Node;


@interface List : Object {
  Node *head;
  Node *tail;
  Node *next;
  Node *curr;
  int size;
}

- append:(id)item;
- remove:(id)item;

- (int)findIndexOf:(id)item;
- (id)itemAtIndex:(int)index;

- (id)head;
- (id)tail;

- (int)size;

@end


@interface List (Iterator)
- iterate;
- (id)next;
@end


@interface List (Current)
- setCurrent:(id)currentItem;
- (id)current;
@end

