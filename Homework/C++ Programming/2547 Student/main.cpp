#include "Student.h"
#include "Date.h"

void testDate(Date& d) {
 Date test(d);
 if (test == d)
  cout << test.toString() << " == " << d.toString() << endl;
 if (test.getDay() > 1) {
  test.setDay(test.getDay()-1);
 } else if (test.getMonth() > 1) {
  test.setMonth(test.getMonth()-1);
 } else {
  test.setYear(test.getYear()-1);
 }
 if (test < d)
  cout << test.toString() << " < " << d.toString() << endl;
 if (d > test)
  cout << d.toString() << " > " << test.toString() << endl;
}

void testStudent(Student& s) {
 s.sayHi();
 int year, month, day;
 cin >> year >> month >> day;
 Date date(year, month, day);
 string name;
 int age;
 cin >> name >> age;
 s.set(name);
 s.set(age);
 s.set(date);

 Person *p = &s;
 p->sayHi();
}


int main() {
 string dateString;
 cin >> dateString;
 Date date(dateString);
 testDate(date);

 string name;
 int age;
 cin >> name >> age;
 Student s(name, age, date);
 testStudent(s);

 return 0;
}