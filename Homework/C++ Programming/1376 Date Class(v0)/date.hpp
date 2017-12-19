// Written by Matrix
#ifndef DATE_HPP_
#define DATE_HPP_
#include <string>
#include <cstdio>

class Date {

 public:
  void setDate(int year, int month, int day);
  int year() const;
  int month() const;
  int day() const;

  std::string toString() const {
    const int length_of_date_string = 10;

    char date_string[length_of_date_string + 1];
    snprintf(date_string,
            length_of_date_string + 1,
            "%04d-%02d-%02d",
            year_, month_, day_);

    return std::string(date_string);
  }

  void increment();
  void decrement();

 private:
  int year_;
  int month_;
  int day_;

  int daysOfMonth(int year, int month) const;
};

#endif
