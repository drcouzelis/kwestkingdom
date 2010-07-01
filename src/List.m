#include <string.h>

#import "List.h"


#define NODE_NAME_LENGTH 256


@interface Node : Object {
  id item;
  char name[NODE_NAME_LENGTH];
  Node *next;
  Node *prev;
}
- setItem:(id)anItem;
- setNext:(Node *)node;
- setPrev:(Node *)node;
- setName:(char *)aName;
- (id)item;
- (Node *)next;
- (Node *)prev;
- (char *)name;
@end


@interface List (Private)
- removeNode:(Node *)node;
@end


@implementation Node


- setItem:(id)anItem {
  item = anItem;
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


- setName:(char *)aName {
  strncpy(name, aName, NODE_NAME_LENGTH);
  return self;
}


- (id)item {
  return item;
}


- (Node *)next {
  return next;
}


- (Node *)prev {
  return prev;
}


- (char *)name {
  return name;
}


@end


@implementation List


- free {
  while (![self isEmpty]) {
    [[self pop] free];
  }
  return [super free];
}


- (int)size {
  return size;
}


@end


@implementation List (Insert)


- insert:(id)item {
  
  if (!item) {
    return self;
  }
  
  Node *node = [[Node alloc] init];
  [node setItem:item];
  
  // Put the new node at the head of the list
  if (!tail) {
    tail = node;
  } else {
    [head setPrev:node];
    [node setNext:head];
  }
  head = node;
  
  size++;
  
  return self;
}


- insert:(id)item named:(char *)name {
  [self insert:item];
  [tail setName:name];
  return self;
}


- push:(id)item {

  if (!item) {
    return self;
  }
  
  Node *node = [[Node alloc] init];
  [node setItem:item];
  
  // Put the new node at the tail of the list
  if (!head) {
    head = node;
  } else {
    [node setPrev:tail];
    [tail setNext:node];
  }
  tail = node;
  
  size++;
  
  return self;
}


- push:(id)item named:(char *)name {
  [self push:item];
  [tail setName:name];
  return self;
}


- enqueue:(id)item {
  return [self push:item];
}


- enqueue:(id)item named:(char *)name {
  return [self push:item named:name];
}


@end


@implementation List (Remove)


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
  
  return [self removeNode:node];
}


- (id)removeItemNamed:(char *)name {
  Node *node = head;
  while (node && strncmp([node name], name, NODE_NAME_LENGTH) != 0) {
    node = [node next];
  }
  return [self removeNode:node];
}


- (id)removeItemAtIndex:(int)index {

  if (index < 0 || index >= size) {
    return nil;
  }
  
  Node *node = head;
  int count = 0;
  
  while (count < index) {
    node = [node next];
    count++;
  }
  
  return [self removeNode:node];
}


- (id)pop {
  return [self removeNode:tail];
}


- (id)dequeue {
  return [self removeNode:head];
}


@end


@implementation List (Retrieve)


- (id)itemAtIndex:(int)index {
  
  Node *node = head;
  int count = 0;
  
  if (index < 0 || index >= size) {
    return nil;
  }
  
  while (count < index) {
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


- (id)first {
  return [head item];
}


- (id)last {
  return [tail item];
}


@end


@implementation List (Query)


- (BOOL) isEmpty {
  if (size == 0) {
    return YES;
  }
  return NO;
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


@end


@implementation List (Iterator)


- iterate {
  next = head;
  return self;
}


- (BOOL)hasNext {
  if (next) {
    return YES;
  }
  return NO;
}


- (id)next {
  id item = [next item];
  next = [next next]; // :-P
  return item;
}


@end


@implementation List (Private)


- removeNode:(Node *)node {

  if (!node) {
    return self;
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


@end

