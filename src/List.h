#import <objc/Object.h>


@class Node;


@interface List : Object {
  Node *head;
  Node *tail;
  int size;
}

- freeIncludingItems; // Call "free" to keep the items in memory

- add:(id)item;
- add:(id)item named:(char *)name;

- (id)remove:(id)item; // Returns a pointer to the item
- (id)removeItemNamed:(char *)name; // This one does too

- (id)itemAtIndex:(int)index;
- (id)itemNamed:(char *)name;

- (int)findIndexOf:(id)item;

- (id)head; // Returns a pointer to the first item in the list...
- (id)tail; // ...and the last item in the list

- (int)size;

@end


@interface Iterator : Object {
  List *list;
  Node *next;
}
- initList:(List *)aList;
- (BOOL)hasNext;
- (id)next;
@end

