// MegaShow
#ifndef STACK_H_
#define STACK_H_

#include <iostream>
#include <queue>
using std::queue;
using std::cout;
using std::endl;

template <class type>
class Stack {
  public:
    Stack() : count(0) {} // constructor.
    
    void push(const type& data) {
        if (q2.empty()) {
            q1.push(data);
        } else {
            q2.push(data);
        }
        count++;
    } // push operation.

    type pop() {
        if (q2.empty() && q1.empty()) {
            return static_cast<type>(0);
        } else if (q2.empty()) {
            while (q1.size() != 1) {
                q2.push(q1.front());
                q1.pop();
            }
            type var = q1.front();
            q1.pop();
            count--;
            return var;
        } else {
            while (q2.size() != 1) {
                q1.push(q2.front());
                q2.pop();
            }
            type var = q2.front();
            q2.pop();
            count--;
            return var;
        }
    } // return the value in the top and pop it out of the stack.
    
    type top() {
        if (q2.empty() && q1.empty()) {
            return static_cast<type>(0);
        } else if (q2.empty()) {
            return q1.back();
        } else {
            return q2.back();
        }
    } // return the value in top.

    int size() const {
        return count;
    }  // return size of the stack.

    bool empty() {
        return count == 0;
    } // check whether is empty.

  private:
    queue<type> q1; // two queues.
    queue<type> q2;
    int count; // the number of elements.
};


template <class type>
void print(Stack<type> s) {
    while (!s.empty()) {
        cout << s.pop() << ' ';
    }
    cout << endl;
}

#endif
