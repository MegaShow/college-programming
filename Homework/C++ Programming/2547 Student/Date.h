// MegaShow
#ifndef DATE_H_
#define DATE_H_

#include <sstream>
#include <string>
using namespace std;

class Date {
  private:
    int _year;
    int _month;
    int _day;
  public:
    Date(int y, int m, int d) {
        _year = y; _month = m; _day = d;
    }

    Date(string& dateString) {
        char tmp;
        std::stringstream ss;
        ss << dateString;
        ss >> _year >> tmp >> _month >> tmp >> _day;
    }

    Date(const Date& t) {
        _year = t._year;
        _month = t._month;
        _day = t._day;
    }

    int getYear() const { return _year; }
    void setYear(int y) { _year = y; }
    int getMonth() const { return _month; }
    void setMonth(int m) { _month = m; }
    int getDay() const { return _day; }
    void setDay(int d) { _day = d; }

    bool operator==(Date& other) const {
        return _year == other._year && _month == other._month && _day == other._day;
    }
    bool operator<(Date& other) const {
        if(_year < other._year)
            return true;
        else if(_year == other._year && _month < other._month) {
            return true;
        }
        else if(_year == other._year && _month == other._month && _day < other._day) {
            return true;
        }
        else {
            return false;
        }
    }
    bool operator>(Date& other) const {
        return !(*this == other || *this < other);
    }

    std::string toString() const {
        std::string str;
        std::stringstream ss;
        ss << _year << "-" << _month << "-" << _day;
        ss >> str;
        return str;
    }
};

#endif
