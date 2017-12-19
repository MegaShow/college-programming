// Written by Matrix
#ifndef DATE_HPP_
#define DATE_HPP_
#include <string>
#include <cstdio>

class Date {
public:
  Date();
  Date(int, int, int);
  bool equals(const Date&) const;
  bool smallerThan(const Date&) const;

  void setDate(int _year, int _month, int _day) {
    year = _year;
    month = _month;
    day = _day;
    normalize();
  }
  int getYear() const {
    return year;
  }
  int getMonth() const {
    return month;
  }
  int getDay() const {
    return day;
  }

  std::string toString() const {
    const int length_of_date_string = 10;

    char date_string[length_of_date_string + 1];
    snprintf(date_string,
      length_of_date_string + 1,
      "%04d-%02d-%02d",
      year, month, day);

    return std::string(date_string);
  }

  void increment() {
    ++day;
    if (day > daysOfMonth(year, month)) {
      day = 1;
      ++month;
      if (month > 12) {
        month = 1;
        ++year;
      }
    }
  }

  void decrement() {
    --day;
    if (day < 1) {
      --month;
      if (month < 1) {
        month = 12;
        --year;
      }
      day = daysOfMonth(year, month);
    }
  }

private:
  int year;
  int month;
  int day;

  int daysOfMonth(int year, int month) const {
    if (month == 2) {
      return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : 28;
    } else {
      int daysOfMonth[13] = { -1, 31, -1, 31, 30,
        31, 30, 31, 31,
        30, 31, 30, 31 };
      return daysOfMonth[month];
    }
  }

  void normalize();
};

#endif
