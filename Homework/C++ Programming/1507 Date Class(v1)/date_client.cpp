// Written by Matrix
#include "date.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void TestDates(const Date& date0, const Date& date1, Date& date2) {
  cout << date1.toString() << endl;
  cout << date2.toString() << endl;

  cout << (date0.equals(date1) ? "D0 == D1" :
    date0.smallerThan(date1) ? "D0 < D1" : "D0 > D1") << endl;

  cout << (date0.equals(date2) ? "D0 == D2" :
    date0.smallerThan(date2) ? "D0 < D2" : "D0 > D2") << endl;

  cout << (date1.equals(date2) ? "D1 == D2" :
    date1.smallerThan(date2) ? "D1 < D2" : "D1 > D2") << endl;
}

int main() {
  int year1, month1, day1;
  int year2, month2, day2;
  cin >> year1 >> month1 >> day1;
  cin >> year2 >> month2 >> day2;

  Date date0;
  Date date1(year1, month1, day1);
  Date date2(year2, month2, day2);

  TestDates(date0, date1, date2);

  return 0;
}

/*
One probable test case:

2016 12 32
2015 18 1
2017-01-01
2016-06-01
D0 > D1
D0 > D2
D1 > D2

*/
