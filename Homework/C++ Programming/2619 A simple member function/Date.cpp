// MegaShow
#include "Date.hpp"

bool Date::isEarlierThan(const Date& newdate) const {
    if (year < newdate.year) {
        return true;
    } else if (year == newdate.year && month < newdate.month) {
        return true;
    } else if (year == newdate.year && month == newdate.month && day < newdate.day) {
        return true;
    } else {
        return false;
    }
}
