#include <iostream>
#include <cstring>
#include "String.h"
#include <string>
using namespace std;
 
String a, b("MFGZ!");
String c = b;
 
void display() {
  cout << a.empty() << " " << a.length() << " " << a << endl;
  cout << b.empty() << " " << b.length() << " " << b << endl;
  cout << c.empty() << " " << c.length() << " " << c << endl;
}
 
int main() {
  string aa, bb, cc;
  display();
  c[0] = 'K';
  display();
  cin >> aa >> cc;
  a.assign(aa.c_str());
  c.assign(cc.c_str());
  display();
  b.clear();
  display();
  for (int i = 0 ; i < 10; ++i) {
      char t;
      cin >> t;
      a.append(t);
      b.append(t);
      c.append(t);
  }
  display();
  b = c;
  display();
  b = a + c;
  display();
  cout << a.find(String("1993")) << endl;
  cout << b.find(String("HYOUKA")) << endl;
  cout << c.find(String("RIKKA")) << endl;
  cout << a.substr(0, 3) << endl;
  cout << b.substr(3, 8) << endl;
  cout << c.substr(6, 1) << endl;
  cout << (a > b) << (a >= b) << (a < b) << (a <= b) << (a == b) << endl;
  cout << a.compare(b) << b.compare(a) << endl;
  cout << (a > c) << (a >= c) << (a < c) << (a <= c) << (a == c) << endl;
  cout << a.compare(c) << c.compare(a) << endl;
  b = a;
  cout << (a > b) << (a >= b) << (a < b) << (a <= b) << (a == b) << endl;
  cout << a.compare(b) << b.compare(a) << endl;
  cout << a.compare(a) << endl;
  return 0;
}
 