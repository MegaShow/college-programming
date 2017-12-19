// MegaShow
#ifndef INSERVICE_H_
#define INSERVICE_H_

#include <string>
#include <iostream>

class Person {
protected:
    std::string name;
    int sex;
public:
    Person() {
        std::cout << "Construct Person" << std::endl;
    }

    ~Person() {
        std::cout << "Destruct Person" << std::endl;
    }

    std::string getName() {
        return name;
    }

    int getSex() {
        return sex;
    }
};


class Student :public virtual Person {
protected:
    std::string sno;
public:
    Student() {
        std::cout << "Construct Student" << std::endl;
    }

    ~Student() {
        std::cout << "Destruct Student" << std::endl;
    }

    std::string getSno() {
        return sno;
    }
};


class Worker :public virtual Person {
protected:
    std::string wno;
public:
    Worker() {
        std::cout << "Construct Worker" << std::endl;
    }

    ~Worker() {
        std::cout << "Destruct Worker" << std::endl;
    }

    std::string getWno() {
        return wno;
    }
};


class InService :public Student, public Worker {
public:
    InService(std::string _name, int _sex, std::string _sno, std::string _wno) {
        name = _name;
        sex = _sex;
        sno = _sno;
        wno = _wno;
        std::cout << "Construct InService" << std::endl;
    }

    ~InService() {
        std::cout << "Destruct InService" << std::endl;
    }
};

#endif