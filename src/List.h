#import <objc/Object.h>


@class Node;


@interface List : Object {
  Node *head;
  Node *tail;
  int size;
  Node *next; // For the iterator
  BOOL ownsItems; // If true, it will free the items when deallocating the list
}
- ownsItems:(BOOL)flag;
- (int)size;
@end


@interface List (Insert)
- insert:(id)item;
- insert:(id)item named:(char *)name;
- push:(id)item;
- push:(id)item named:(char *)name;
- enqueue:(id)item;
- enqueue:(id)item named:(char *)name;
@end


@interface List (Remove)
- (id)remove:(id)item; // Returns a pointer to the item
- (id)removeItemNamed:(char *)name; // This one does too
- (id)removeItemAtIndex:(int)index;
- (id)pop;
- (id)dequeue;
@end


@interface List (Retrieve)
- (id)itemAtIndex:(int)index;
- (id)itemNamed:(char *)name;
- (id)first; // Returns a pointer to the first item in the list...
- (id)last; // ...and the last item in the list
@end


@interface List (Query)
- (BOOL)isEmpty;
- (int)findIndexOf:(id)item;
@end


@interface List (Iterator)
- iterate;
- (BOOL)hasNext;
- (id)next;
@end

