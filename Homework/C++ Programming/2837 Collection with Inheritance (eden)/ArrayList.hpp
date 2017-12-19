#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#include "List.hpp"

class ArrayList : public List {
 public:
  ArrayList();
  ~ArrayList();
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
  E* storage;
  int _size;
  int _maxsize;
  static const int extend_factor = 2;
  void extend(void);
};

#endif

