#ifndef STACK_HPP_
#define STACK_HPP_
#define MAX_SIZE 10
typedef int E;

class stack {
private:
  E * storage;
  int max_size;
  int size;
public:
  stack() {
    this->storage = new E[MAX_SIZE];
    this->max_size = MAX_SIZE;
    this->size = 0;
  }
  ~stack();
  void push(E ele);
  void pop();
  E top();
  bool isEmpty();
  bool isFull();
  void clear();
};

#endif
