#include "BookItem.h"
#include "BulkItem.h"
#include <iostream>
#include <string>
#include <cstdio>
using std::cout;
using std::cin;
using std::endl;
using std::string;
 int main() {
  string name1;
  double price1;
  int num1;
  cin >> name1 >> price1 >> num1;
  BookItem boi1(name1, price1);
  cout << boi1.getName() << endl;
  printf("%.2lf\n", boi1.netPrice(num1));
   string name2;
  double price2;
  int num2;
  cin >> name2 >> price2 >> num2;
  BulkItem bui1(name2, price2);
  cout << bui1.getName() << endl;
  printf("%.2lf\n", bui1.netPrice(num2));
   string name3;
  double price3, disc3;
  int qty3, num3;
  cin >> name3 >> price3 >> qty3 >> disc3 >> num3;
  BulkItem bui2(name3, price3, qty3, disc3);
  cout << bui2.getName() << endl;
  printf("%.2lf\n", bui2.netPrice(num3));
   return 0;
}
 