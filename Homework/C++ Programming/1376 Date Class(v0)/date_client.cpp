// Written by Matrix
#include "date.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void TestDate(Date& date, int after, int before) {
  cout << "Year: " << date.year() << endl
       << "Month: " << date.month() << endl
       << "Day: " << date.day() << endl;
  cout << "Formatted: " << date.toString() << endl;

  date.increment();
  cout << "1 day later: " << date.toString() << endl;
  for (int i = 0; i < after; ++i) {
    date.increment();
  }
  cout << "Another " << after << " day(s) later: " << date.toString() << endl;
  for (int i = 0; i < before; ++i) {
    date.decrement();
  }
  cout << "Another " << before << " day(s) earlier: " << date.toString() << endl;
}

int main() {
  int year, month, day;
  int after, before;
  cin >> year >> month >> day;
  cin >> after >> before;

  Date date;
  date.setDate(year, month, day);
  TestDate(date, after, before);

  return 0;
}

/*
One probable test case:

1900 2 28 365 366
Year: 1900
Month: 2
Day: 28
Formatted: 1900-02-28
1 day later: 1900-03-01
Another 365 day(s) later: 1901-03-01
Another 366 day(s) earlier: 1900-02-28

*/
