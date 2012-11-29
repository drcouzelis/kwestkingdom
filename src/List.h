#import <Foundation/Foundation.h>


@interface Node : NSObject {
  id item;
  Node *next;
  Node *prev;
}


- setItem: (id) anItem;
- setNext: (Node *) theNext;
- setPrev: (Node *) thePrev;
- (id) getItem;
- (Node *) getNext;
- (Node *) getPrev;


@end


@interface List : NSObject {
  Node *head;
  Node *tail;
  Node *next;
  int size;
}


- append: (id) item;
- remove: (id) item;

- (int) findIndex: (id) item;
- (id) getIndex: (int) index;

- (id) getHead;
- (id) getTail;

- iterate;
- (id) next;

- (int) size;


@end
