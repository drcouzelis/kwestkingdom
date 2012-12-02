#ifndef LIST_HEADER
#define LIST_HEADER


#include <Foundation/Foundation.h>


class Node : public NSObject {
  id item;
  Node *next;
  Node *prev;
public:


  setItem: (id) anItem;
  setNext: (Node *) theNext;
  setPrev: (Node *) thePrev;
  (id) getItem;
  (Node *) getNext;
  (Node *) getPrev;


};


class List : public NSObject {
  Node *head;
  Node *tail;
  Node *next;
  int size;
public:


  append: (id) item;
  remove: (id) item;

  (int) findIndex: (id) item;
  (id) getIndex: (int) index;

  (id) getHead;
  (id) getTail;

  iterate;
  (id) next;

  (int) size;


};


#endif