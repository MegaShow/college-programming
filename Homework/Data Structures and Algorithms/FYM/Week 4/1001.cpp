// 1001. 链栈
enum ErrorCode {
  success,
  underflow,
  overflow
};

template <class StackEntry>
struct Node {
  StackEntry data;
  Node *next;
};

template <class StackEntry>
class MyStack {
 public:
  MyStack();
  /*
    判断栈是否为空，若为空则返回true，非空则返回false
   */
  bool empty() const;
  int size() const;
  /*
    出栈操作，若正常出栈则返回success，若栈内无元素则返回underflow
   */
  ErrorCode pop();
  /*
    获取栈顶元素，若正常获取到栈顶元素则返回success，若栈内无元素则返回underflow
    元素内容保存在引用参数item中
   */
  ErrorCode top(StackEntry &item) const;
  /*
    入栈操作，若正常入栈则返回success，若入栈失败则返回overflow
   */
  ErrorCode push(const StackEntry &item);
  /*
    清空栈
   */
  void clear();

 private:
  // 请不要修改数据成员.
  Node<StackEntry> *pTop;
};

template <class StackEntry>
MyStack<StackEntry>::MyStack(): pTop(nullptr) {}

template <class StackEntry>
bool MyStack<StackEntry>::empty() const {
  return pTop == nullptr;
}

template <class StackEntry>
int MyStack<StackEntry>::size() const {
  Node<StackEntry>* it = pTop;
  int val = 0;
  while (it != nullptr) {
    val++;
    it = it->next;
  }
  return val;
}

template <class StackEntry>
ErrorCode MyStack<StackEntry>::pop() {
  if (pTop == nullptr) return underflow;
  Node<StackEntry>* tmp = pTop;
  pTop = pTop->next;
  delete tmp;
  return success;
}

template <class StackEntry>
ErrorCode MyStack<StackEntry>::top(StackEntry &item) const {
  if (pTop == nullptr) return underflow;
  item = pTop->data;
  return success;
}

template <class StackEntry>
ErrorCode MyStack<StackEntry>::push(const StackEntry &item) {
  Node<StackEntry>* tmp = new Node<StackEntry>;
  if (tmp == nullptr) return overflow;
  tmp->data = item;
  tmp->next = pTop;
  pTop = tmp;
  return success;
}

template <class StackEntry>
void MyStack<StackEntry>::clear() {
  while (pTop != nullptr) {
    Node<StackEntry>* tmp = pTop;
    pTop = pTop->next;
    delete tmp;
  }
}

int main() {}
