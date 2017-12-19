#include <iostream>
#include "Date.hpp"
using namespace std;

int main() {
    int year1,month1,day1,year2,month2,day2;
    cin>>year1>>month1>>day1;
    cin>>year2>>month2>>day2;

    cout<<Date(year1,month1,day1).isEarlierThan(Date(year2,month2,day2));

    return 0;
}
