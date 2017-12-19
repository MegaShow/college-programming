#include "source.h"
#include <iostream>
using namespace std;

int main() {
  int value;
  cin >> value;
  Calculator counter(value);
  int i;
  for (i = 0; i < 5; i++) {
    ++counter;
  }
  for (i = 0; i <= 7; i++) {
    --counter;
  }
}
