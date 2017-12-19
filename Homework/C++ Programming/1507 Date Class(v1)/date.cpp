// MegaShow
// [06] Date Class(v1)
#include "date.hpp"

Date::Date(){
  setDate(2017, 1, 28);
}

Date::Date(int _year, int _month, int _day){
  setDate(_year, _month, _day);
}

bool Date::equals(const Date tmp) const{
  if(tmp.getYear() == year && tmp.getMonth() == month && tmp.getDay() == day)
     return true;
  return false;
}

bool Date::smallerThan(const Date tmp) const{
   if(year < tmp.getYear())
       return true;
   else if(tmp.getYear() == year && month < tmp.getMonth())
       return true;
   else if(tmp.getYear() == year && tmp.getMonth() == month && day < tmp.getDay())
       return true;
   return false;
}

void Date::normalize(){
  //if(year < 100)
  //   year += 1900;
  if(month > 12){
     year += month / 12;
     month %= 12;
     if(month == 0){
           year--;
           month = 12;
         }
   }
  while(day > daysOfMonth(year, month)){
     day -= daysOfMonth(year, month);
     month++;
     if(month > 12){
           month = 1;
           year++;
         }
   }
}
