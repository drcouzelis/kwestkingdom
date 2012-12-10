#include <stdio.h>

#include "List.h"





Node::Node() {
  item = NULL;
  next = NULL;
  prev = NULL;
}


void Node::setItem(void *anItem) {
  item = anItem;

}


void Node::setNext(Node * theNext) {
  next = theNext;

}


void Node::setPrev(Node * thePrev) {
  prev = thePrev;

}


void * Node::getItem() {
  return item;
}


Node * Node::getNext() {
  return next;
}


Node * Node::getPrev() {
  return prev;
}








List::List() {
  
  head = NULL;
  tail = NULL;
  next = NULL;
  size = 0;
}


List::~List() {
  
  Node *node;
  Node *tmp;
  
  node = head;
  
  while (node != NULL) {
    tmp = node->getNext();
    delete node->getItem();
    delete node;
    node = tmp;
  }


}


void List::append(void *item) {
  
  Node *node;
  
  node = new Node();
  node->setItem(item);
  
  if (head == NULL) {
    head = node;
  } else {
    node->setPrev(tail);
    tail->setNext(node);
  }
  
  tail = node;
  size++;
  

  
}


void List::remove(void *item) {
  
  Node *node;
  
  node = head;
  
  while (node != NULL && node->getItem() != item) {
    node = node->getNext();
  }
  
  if (node == NULL) {
    return;
  }
  
  if (node == head && node == tail) {
    head = NULL;
    tail = NULL;
  }
  
  if (node == head) {
    head = head->getNext();
    head->setPrev(NULL);
  } else if (node == tail) {
    tail = tail->getPrev();
    tail->setNext(NULL);
  } else {
    node->getPrev()->setNext(node->getNext());
    node->getNext()->setPrev(node->getPrev());
  }
  
  delete node;
  size--;
}


int List::findIndex(void *item) {
  
  Node *node;
  int index;
  
  node = head;
  index = 0;
  
  if (item == NULL) {
    return -1;
  }
  
  while (node != NULL && node->getItem() != item) {
    node = node->getNext();
    index++;
  }
  
  if (node == NULL) {
    return -1;
  }
  
  return index;
  
}


void * List::getIndex(int index) {
  
  Node *node;
  int count;
  
  node = head;
  count = 0;
  
  if (index < 0) {
    return NULL;
  }
  
  while (node != NULL && count != index) {
    node = node->getNext();
    count++;
  }
  
  if (node == NULL) {
    return NULL;
  }
  
  return node->getItem();
  
}


void List::iterate() {
  next = head;

}


void * List::getHead() {
  return head->getItem();
}


void * List::getTail() {
  return tail->getItem();
}


void * List::getNext() {
  
  void * item;
  
  if (next == NULL) {
    return NULL;
  }
  
  item = next->getItem();
  next = next->getNext();
  
  return item;
  
}


int List::getSize() {
  return size;
}



