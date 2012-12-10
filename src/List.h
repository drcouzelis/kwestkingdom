#ifndef LIST_HEADER
#define LIST_HEADER


class Node {

protected:

  void *item;
  Node *next;
  Node *prev;

public:

  Node();

  void setItem(void *anItem);
  void setNext(Node *theNext);
  void setPrev(Node *thePrev);
  void *getItem();
  Node *getNext();
  Node *getPrev();
};


class List {

protected:

  Node *head;
  Node *tail;
  Node *next;
  int size;

public:

  List();
  ~List();

  void append(void *item);
  void remove(void *item);

  int findIndex(void *item);
  void *getIndex(int index);

  void *getHead();
  void *getTail();

  void iterate();
  void *getNext();

  int getSize();
};


#endif
