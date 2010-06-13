#import "List.h"


@interface Node : Object {
  id item;
  Node *next;
  Node *prev;
}
- setItem:(id)anItem;
- setNext:(Node *)node;
- setPrev:(Node *)node;
- (id)item;
- (Node *)next;
- (Node *)prev;
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


- (id)item {
  return item;
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
  
  Node *node;
  Node *tmp;
  
  node = head;
  
  while (node) {
    tmp = [node next];
    [[node item] free];
    [node free];
    node = tmp;
  }
  
  return [super free];
}


- append:(id)item {
  
  Node *node;
  
  node = [[Node alloc] init];
  [node setItem:item];
  
  if (head == nil) {
    head = node;
  } else {
    [node setPrev: tail];
    [tail setNext: node];
  }
  
  tail = node;
  size++;
  
  return self;
}


- remove:(id)item {
  
  Node *node;
  
  node = head;
  
  while (node && [node item] != item) {
    node = [node next];
  }
  
  if (!node) {
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
  
  return self;
}


- (int)findIndexOf:(id)item {
  
  Node *node;
  int index;
  
  node = head;
  index = 0;
  
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


- (id)itemAtIndex:(int)index {
  
  Node *node;
  int count;
  
  node = head;
  count = 0;
  
  if (index < 0) {
    return nil;
  }
  
  while (node && count != index) {
    node = [node next];
    count++;
  }
  
  if (!node) {
    return nil;
  }
  
  return [node item];
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


@implementation List (Iterator)


- iterate {
  next = head;
  return self;
}


- (id)next {
  
  id item;
  
  if (!next) {
    return nil;
  }
  
  item = [next item];
  next = [next next];
  
  return item;
}


@end

