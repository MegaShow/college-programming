#include <iostream>
#include <string>
#include "cmp.h"
using std::cout;
using std::endl;
using std::string;
int main() {
     int aInt = 1, bInt = 2;
     double aDouble = 3.0, bDouble = 3.0;
     char aChars[5] = "haha", bChars[5] = "hahb";
     char taChars[6] = "trick", tbChars[6] = "trick";
     string aStr = "haha", bStr = "aha";
     int* aIntPtr = &aInt, *bIntPtr = &bInt;
      cout << cmp(aInt, bInt)<< endl;
     cout << cmp(aDouble, bDouble)<< endl;
      cout << cmp(aChars, bChars)<< endl;
     cout << cmp(taChars, tbChars)<< endl;
     cout << cmp(aStr, bStr)<< endl;
     cout << cmp(aIntPtr, bIntPtr)<< endl;
     cout << cmp(&aDouble, &bDouble) << endl;
     return 0;
}
  