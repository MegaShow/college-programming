// MegaShow

const int MAX_LEN = 5;

template<class type>
class Stack {
  public:
    explicit Stack() : stack_size(0) {}

    bool empty() const {
      return stack_size == 0;
    }

    int size() const {
      return stack_size;
    }

    type& top() {
      if (stack_size == 0) {
        throw 1;
      }
      return data[stack_size-1];
    }

    const type& top() const {
      if (stack_size == 0) {
        throw 1;
      }
      return data[stack_size-1];
    }

    void push(const type& x) {
      if (stack_size == MAX_LEN && x <= data[stack_size-1]) {
        return;
      } else if (stack_size == MAX_LEN) {
        data[stack_size-1] = x;
      } else {
        data[stack_size++] = x;
      }
    }

    void pop() {
      if (stack_size == 0) {
        throw 0.1;
      }
      stack_size--;
    }

  private:
    type data[MAX_LEN];
    int stack_size;
};