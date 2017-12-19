#ifndef STANDARD_HPP
#define STANDARD_HPP
#include <iostream>
using namespace std;
class B {
private:
  int x;
  int y;

public:
  B(int a, int b) {
    x = a;
    y = b;
  }
  void print() const { cout << x << ", " << y << endl; }
};

class D : public B {
private:
  B member;
  int k;

public:
  D(int, int, int, int, int);
  void print(void) const;
};
#endif
