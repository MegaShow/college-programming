// 1000. 链式队列
enum ErrorCode {
  success,
  underflow,
  overflow
};

template <class QueueEntry>
struct Node {
  QueueEntry data;
  Node<QueueEntry> *next;
};

template <class QueueEntry>
class MyQueue {
 public:
  MyQueue();
  // 判断队列是否为空
  bool empty() const;
  // 入队操作
  ErrorCode append(const QueueEntry &item);
  // 出队操作
  ErrorCode serve();
  // 获取队头元素
  ErrorCode retrieve(QueueEntry &item) const;
  // 获取队列已有元素个数
  int size() const;
  // 清除队列所有元素
  void clear();
  // 获取队头元素并出队
  ErrorCode retrieve_and_serve(QueueEntry &item);

 private:
  // 请不要修改数据成员.
  Node<QueueEntry> *front;                           // 队头指针
  Node<QueueEntry> *rear;                             // 队尾指针
};

template <class QueueEntry>
MyQueue<QueueEntry>::MyQueue(): front(nullptr), rear(nullptr) {}

template <class QueueEntry>
bool MyQueue<QueueEntry>::empty() const {
  return front == nullptr;
}

template <class QueueEntry>
ErrorCode MyQueue<QueueEntry>::append(const QueueEntry &item) {
  if (front == nullptr) {
    front = rear = new Node<QueueEntry>;
    front->data = item;
    front->next = nullptr;
    return success;
  }
  rear->next = new Node<QueueEntry>;
  rear = rear->next;
  rear->data = item;
  rear->next = nullptr;
  return success;
}

template <class QueueEntry>
ErrorCode MyQueue<QueueEntry>::serve() {
  if (front == nullptr) return underflow;
  Node<QueueEntry>* tmp = front;
  front = front->next;
  if (front == nullptr) rear = nullptr;
  delete tmp;
  return success;
}

template <class QueueEntry>
ErrorCode MyQueue<QueueEntry>::retrieve(QueueEntry &item) const {
  if (front == nullptr) return underflow;
  item = front->data;
  return success;
}

template <class QueueEntry>
ErrorCode MyQueue<QueueEntry>::retrieve_and_serve(QueueEntry &item) {
  ErrorCode status = retrieve(item);
  if (status == success) return serve();
  return status;
}

template <class QueueEntry>
int MyQueue<QueueEntry>::size() const {
  Node<QueueEntry>* it = front;
  int val = 0;
  while (it != rear) {
    val++;
    it = it->next;
  }
  if (rear != nullptr) val++;
  return val;
}

template <class QueueEntry>
void MyQueue<QueueEntry>::clear() {
  while (front != rear) {
    if (front) {
      Node<QueueEntry>* tmp = front;
      front = front->next;
      delete tmp;
    }
  }
  if (front != nullptr) delete front;
  front = rear = nullptr;
}

int main() {}
