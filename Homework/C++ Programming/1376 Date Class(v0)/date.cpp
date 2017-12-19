// MegaShow
// [01] Date Class
#include "date.hpp"

int Date::daysOfMonth(int year, int month) const{
    int arr[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
        if(month == 2)
            return 29;
        else
            return arr[month];
    }
    else
        return arr[month];
}

void Date::increment(){
    if(daysOfMonth(year_, month_) == day_){
        if(month_ == 12){
            year_++;
            month_ = 1;
            day_ = 1;
        }
        else{
            month_++;
            day_ = 1;
        }
    }
    else
        day_++;
}

void Date::decrement(){
    if(day_ == 1){
        if(month_ == 1){
            year_--;
            month_ = 12;
            day_ = 31;
        }
        else{
            month_--;
            day_ = daysOfMonth(year_, month_);
        }
    }
    else
        day_--;
}

int Date::year() const{
    return year_;
}

int Date::month() const{
    return month_;
}

int Date::day() const{
    return day_;
}

void Date::setDate(int year, int month, int day){
    year_ = year;
    month_ = month;
    day_ = day;
}
