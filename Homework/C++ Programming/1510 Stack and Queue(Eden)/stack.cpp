// MegaShow
// [08] Stack and Queue(Eden)
#include "stack.hpp"

void stack::push(int var){
  if(isFull())
     return;
  top++;
  storage[top] = var;
}

void stack::pop(void){
  if(isEmpty())
     return;
  top--;
}

int stack::peek(void){
  if(isEmpty())
     return 0;
  return storage[top];
}

bool stack::isEmpty(void){
  if(top == -1)
     return true;
  return false;
}

bool stack::isFull(void){
  if(top == max_size - 1)
     return true;
  return false;
}

void stack::clear(void){
  top = -1;
}
