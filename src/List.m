#include <string.h>

#import "List.h"


#define NODE_NAME_LENGTH 256


@interface List (PrivateMethods)
- (Node *)headNode;
@end


@interface Node : Object {
  id item;
  char name[NODE_NAME_LENGTH];
  Node *next;
  Node *prev;
}
- setItem:(id)anItem;
- setName:(char *)aName;
- setNext:(Node *)node;
- setPrev:(Node *)node;
- (id)item;
- (char *)name;
- (Node *)next;
- (Node *)prev;
@end


@implementation Node


- setItem:(id)anItem {
  item = anItem;
  return self;
}


- setName:(char *)aName {
  strncpy(name, aName, NODE_NAME_LENGTH);
  return self;
}


- setNext:(Node *)node {
  next = node;
  return self;
}


- setPrev:(Node *)node {
  prev = node;
  return self;
}


- (id)item {
  return item;
}


- (char *)name {
  return name;
}


- (Node *)next {
  return next;
}


- (Node *)prev {
  return prev;
}


@end


@implementation List


- free {
  while (head) {
    [self remove:[head item]];
  }
  return [super free];
}


- freeIncludingItems {
  while (head) {
    [[head item] free];
    [self remove:[head item]];
  }
  return [super free];
}


- add:(id)item {
  
  if (!item) {
    return self;
  }
  
  Node *node = [[Node alloc] init];
  [node setItem:item];
  
  if (!head) {
    head = node;
  } else {
    [node setPrev: tail];
    [tail setNext: node];
  }
  
  tail = node;
  size++;
  
  return self;
}


- add:(id)item named:(char *)name {
  [self add:item];
  [tail setName:name];
  return self;
}


- (id)remove:(id)item {

  if (!item) {
    return nil;
  }
  
  Node *node = head;
  
  while (node && [node item] != item) {
    node = [node next];
  }
  
  if (!node) {
    // Item not found!
    return nil;
  }
  
  if (node == head && node == tail) {
    head = nil;
    tail = nil;
  }
  
  if (node == head) {
    head = [head next];
    [head setPrev:nil];
  } else if (node == tail) {
    tail = [tail prev];
    [tail setNext:nil];
  } else {
    [[node prev] setNext: [node next]];
    [[node next] setPrev: [node prev]];
  }
  
  [node free];
  size--;
  
  return item;
}


- (id)removeItemNamed:(char *)name {

  Node *node = head;
  
  while (node && strncmp([node name], name, NODE_NAME_LENGTH) != 0) {
    node = [node next];
  }
  
  if (!node) {
    // Item not found!
    return nil;
  }
  
  if (node == head && node == tail) {
    head = nil;
    tail = nil;
  }
  
  if (node == head) {
    head = [head next];
    [head setPrev:nil];
  } else if (node == tail) {
    tail = [tail prev];
    [tail setNext:nil];
  } else {
    [[node prev] setNext: [node next]];
    [[node next] setPrev: [node prev]];
  }
  
  id item = [node item];

  [node free];
  size--;
  
  return item;
}


- (id)itemAtIndex:(int)index {
  
  Node *node = head;
  int count = 0;
  
  if (index < 0) {
    return nil;
  }
  
  while (node && count != index) {
    node = [node next];
    count++;
  }
  
  return [node item];
}


- (id)itemNamed:(char *)name {
  
  Node *node = head;
  
  while (node && strncmp([node name], name, NODE_NAME_LENGTH) != 0) {
    node = [node next];
  }
  
  return [node item];
}


- (int)findIndexOf:(id)item {
  
  Node *node = head;
  int index = 0;
  
  if (!item) {
    return -1;
  }
  
  while (node && [node item] != item) {
    node = [node next];
    index++;
  }
  
  if (!node) {
    return -1;
  }
  
  return index;
}


- (id)head {
  return [head item];
}


- (id)tail {
  return [tail item];
}


- (int)size {
  return size;
}


@end


@implementation List (PrivateMethods)

- (Node *)headNode {
  return head;
}

@end


@implementation Iterator


- initList:(List *)aList {
  self = [self init];
  if (self) {
    list = aList;
    next = [list headNode];
  }
  return self;
}


- (BOOL)hasNext {
  if (next) {
    return YES;
  }
  return NO;
}


- (id)next {
  id item;
  item = [next item];
  next = [next next]; // :-P
  return item;
}


@end

