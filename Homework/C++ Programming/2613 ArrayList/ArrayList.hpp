#ifndef ARRAYLIST_HPP_
#define ARRAYLIST_HPP_
#include <cstddef>
#define DEFAULT_MAX_SIZE 64
typedef int E;

class ArrayList {
 public:
  ArrayList();
  ~ArrayList();

  void add(E e);
  void remove(E e);
  void clear();

  bool contain(E e);
  bool isEmpty();
  E& operator[](int index);
  E& get(int index);
  int indexOf(E element);
  int size();

 private:
  E* storage;
  int _size;
  int _maxsize;
  static const int extend_factor = 2;
  void extend();
};

#endif
