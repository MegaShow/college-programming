#include "Biginteger.h"
#include <iostream>
#include <string>
using namespace std;
 
int main() {
  string s1, s2, s3, s4;
  cin >> s1 >> s2;
  cin >> s4;
  BigInteger a(s1);
  BigInteger b(s2);
  BigInteger c(a);
  BigInteger d(s4);
  BigInteger sum(a+b);
  BigInteger diff(c-d);
  cout << sum << endl;
  cout << diff << endl;
  return 0;
}
 