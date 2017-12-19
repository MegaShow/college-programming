// Written by Matrix
#include <iostream>
#include "EasyString.hpp"

using namespace std;
int main() {
  int length;
  char* str0 = NULL, * str1= NULL;
  cin >> length;
  Assign(str0, length);
  cin >> length;
  Assign(str1, length);
  cin >> str0 >> str1;
  cout << str0 << endl << str1 << endl;
  string res = "";
  AddTwo(res, str0, str1);
  cout << res << endl;
}
