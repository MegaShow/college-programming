#include <iostream>
#include "DouList.h"
using namespace std;
 DouList list1, list2;
 void display() {
  cout << list1.empty() << ':' << list1 << endl;
  cout << list2.empty() << ':' << list2.to_str() << endl;
}
 int main() {
  display();
  list1.push_front(894);
  list2.push_back(2136);
  cout << list1.front() << ',' << list1.back() << endl;
  cout << list2.front() << ',' << list2.back() << endl;
  display();
  list1.push_back(214);
  list2.push_front(931);
  cout << list1.front() << ',' << list1.back() << endl;
  cout << list2.front() << ',' << list2.back() << endl;
  display();
  for (int i = 0; i < 10; ++i) {
    int t;
    cin >> t;
    list1.push_back(t);
    list2.push_front(t);
  }
  display();
  for (int i = 0; i < 5; ++i) {
    list1.pop_front();
    list2.pop_back();
  }
  display();
   DouList list3(list1);
  list1 = list2;
   list1 = list1;
  cout << list1 << endl;
  cout << list3 << endl;
  return 0;
}
 