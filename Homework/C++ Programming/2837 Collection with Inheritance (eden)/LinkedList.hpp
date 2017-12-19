#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "List.hpp"
#include <iostream>

class LinkedList : public List {
 public:
  typedef struct node {
    E data;
    struct node* next;
    struct node* prev;
    node(E data, struct node* next = NULL, struct node* prev = NULL)
        : data(data), next(next), prev(prev) {}
  } node;
  LinkedList();
  ~LinkedList();
  virtual void add(E e);
  virtual void clear(void);
  virtual bool contain(E e);
  virtual bool isEmpty(void);
  virtual void remove(E e);
  virtual E& operator[](int index);
  virtual E& get(int index);
  virtual int indexOf(E element);
  virtual void sort(void);
  virtual int size(void);

 private:
  node* head;
  node* tail;
  int _size;
};

#endif

