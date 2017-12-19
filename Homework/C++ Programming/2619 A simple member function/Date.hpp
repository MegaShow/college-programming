#ifndef DATE_HPP
#define DATE_HPP

class Date {
    public:
        Date(int newYear = 1970, int newMonth = 1,int newDay = 1) {
            this->month = newMonth;
            this->day = newDay;
            this->year = newYear;
        }
        bool isEarlierThan(const Date& newdate) const;
    private:
        int month,day,year;
};

#endif
