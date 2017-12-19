#include "Stack.h"
#include<iostream>
#include<exception>

using namespace std;

class StackForbidden : public exception {
    virtual const char *what() const throw() {
        return "Please do not use Stack in stl..";
    }
};

int main() {

    #if defined(_GLIBCXX_STACK)
        throw StackForbidden();
    #endif

    Stack<int> stack;
    stack.push(88);
    stack.push(44);
    stack.push(99);

    cout << "The size is: " << stack.size() << endl;
    if (!stack.empty()) cout << stack.top() << endl;
    print(stack);

    stack.pop();
    print(stack);

    stack.push(777);
    cout << "The size is: " << stack.size() << endl;
    if (!stack.empty()) cout << stack.top() << endl;
    print(stack);

    stack.pop();
    stack.pop();
    cout << "The size is: " << stack.size() << endl;
    print(stack);
    stack.pop();
    if (!stack.empty()) cout << stack.top() << endl;
    else cout << "it is empty now." << endl;

    Stack<double> stack1;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        stack1.push(i + 0.01);
    }
    print(stack1);
    while (m--) {
        stack1.pop();
    }
    cout << "The size is: " << stack1.size() << endl;
    if (!stack1.empty()) cout << stack1.top() << endl;
    print(stack1);

}
