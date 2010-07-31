/**
 * Copyright 2009 David Couzelis
 * 
 * This file is part of "Kwest Kingdom".
 * 
 * "Kwest Kingdom" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * "Kwest Kingdom" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with "Kwest Kingdom".  If not, see <http://www.gnu.org/licenses/>.
 */
#import <objc/Object.h>


@interface Node : Object {
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


@interface List : Object {
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
