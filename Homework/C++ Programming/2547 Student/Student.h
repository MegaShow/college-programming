// MegaShow
#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include "Date.h"
#include "Person.h"
using namespace std;

class Student : public Person {
private:
    Date graduateDate;
public:
    Student(std::string& _name, int& _age, Date& _date)
    :Person(_name, _age), graduateDate(_date.getYear(), _date.getMonth(), _date.getDay()){}
    
    void set(const Date& d) {
        graduateDate.setYear(d.getYear());
        graduateDate.setMonth(d.getMonth());
        graduateDate.setDay(d.getDay());
    }

    void set(int age) { Person::set(age); }
    void set(string name) { Person::set(name); }

    virtual void sayHi() const {
        Person::sayHi();
        Date d(2017, 5, 7);
        if(graduateDate > d) {
            cout << "I will graduate on " << graduateDate.toString() << "." << endl;
        }
        else if(graduateDate == d) {
            cout << "I graduated today!" << endl;
        }
        else {
            cout << "I have graduated on " << graduateDate.toString() << "."  << endl;
        }
    }
};

#endif