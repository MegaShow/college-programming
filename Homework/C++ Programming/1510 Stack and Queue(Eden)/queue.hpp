// Written by Matrix
#ifndef QUEUE_H_
#define QUEUE_H_
#define MAX_SIZE 10

class queue {
private:
  int * storage;
  int max_size;
  int head;
  int rear;
public:
  queue() {
    // notice the capability is still MAX_SIZE
    this->storage = new int[MAX_SIZE+1]();
    this->max_size = MAX_SIZE+1;
    this->head = 0;
    this->rear = 0;
  }
  ~queue() {
    delete []storage;
  }
  void push(int);
  void pop(void);
  int front(void);
  int back(void);
  bool isFull(void);
  bool isEmpty(void);
  void clear(void);
};

#endif
