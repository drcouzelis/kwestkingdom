#import "List.h"


@implementation Node


- init {
  self = [super init];
  if (self) {
    item = nil;
    next = nil;
    prev = nil;
  }
  return self;
}


- setItem: (id) anItem {
  item = anItem;
  return self;
}


- setNext: (Node *) theNext {
  next = theNext;
  return self;
}


- setPrev: (Node *) thePrev {
  prev = thePrev;
  return self;
}


- (id) getItem {
  return item;
}


- (Node *) getNext {
  return next;
}


- (Node *) getPrev {
  return prev;
}


@end


@implementation List


- init {

  self = [super init];

  if (self) {
    head = nil;
    tail = nil;
    next = nil;
    size = 0;
  }

  return self;

}


- free {

  Node *node;
  Node *tmp;

  node = head;

  while (node != nil) {
    tmp = [node getNext];
    [[node getItem] free];
    [node free];
    node = tmp;
  }

  return self;

}


- append: (id) item {

  Node *node;

  node = [[Node alloc] init];
  [node setItem: item];

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


- remove: (id) item {

  Node *node;

  node = head;

  while (node != nil && [node getItem] != item) {
    node = [node getNext];
  }

  if (node == nil) {
    return nil;
  }

  if (node == head && node == tail) {
    head = nil;
    tail = nil;
  }

  if (node == head) {
    head = [head getNext];
    [head setPrev: nil];
  } else if (node == tail) {
    tail = [tail getPrev];
    [tail setNext: nil];
  } else {
    [[node getPrev] setNext: [node getNext]];
    [[node getNext] setPrev: [node getPrev]];
  }

  [node free];
  size--;

  return self;

}


- (int) findIndex: (id) item {

  Node *node;
  int index;

  node = head;
  index = 0;

  if (item == nil) {
    return -1;
  }

  while (node != nil && [node getItem] != item) {
    node = [node getNext];
    index++;
  }

  if (node == nil) {
    return -1;
  }

  return index;

}


- (id) getIndex: (int) index {

  Node *node;
  int count;

  node = head;
  count = 0;

  if (index < 0) {
    return nil;
  }

  while (node != nil && count != index) {
    node = [node getNext];
    count++;
  }

  if (node == nil) {
    return nil;
  }

  return [node getItem];

}


- iterate {
  next = head;
  return self;
}


- (id) getHead {
  return [head getItem];
}


- (id) getTail {
  return [tail getItem];
}


- (id) next {

  id item;

  if (next == nil) {
    return nil;
  }

  item = [next getItem];
  next = [next getNext];

  return item;

}


- (int) size {
  return size;
}


@end
