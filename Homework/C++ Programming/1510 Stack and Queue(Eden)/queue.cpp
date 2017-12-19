// MegaShow
// [08] Stack and Queue(Eden)
#include "queue.hpp"

void queue::push(int var){
  if(isFull())
     return;
  storage[rear] = var;
  rear++;
  if(rear == max_size)
     rear = 0;
}

void queue::pop(void){
  if(isEmpty())
     return;
  head++;
  if(head == max_size)
     head = 0;
}

int queue::front(void){
  if(isEmpty())
     return 0;
  return storage[head];
}

int queue::back(void){
  if(isEmpty())
     return 0;
  return storage[rear-1];
}

bool queue::isFull(void){
  return rear + 1 == head || (head == 0 && rear == max_size - 1);
}

bool queue::isEmpty(void){
  return rear == head;
}

void queue::clear(void){
  head = 0;
  rear = 0;
}
