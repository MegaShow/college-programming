// MegaShow
#include <string>
#include <sstream>
#include "Account.h"

int Account::_total_account = 0;

Account::Account() {
    reset();
    _total_account++;
}

Account::~Account() {
    _total_account--;
}

int Account::id() const {
    return _id;
}

double Account::balance() const {
    return _balance;
}

bool Account::valid() const {
    return _valid;
}

std::string Account::profile() const {
    std::stringstream ss;
    std::string str;
    ss << "ID:" << _id << "\nBALANCE:";
    ss.precision(6);
    ss.setf(std::ios::fixed, std::ios::floatfield);
    ss << _balance << "\nVALID:N\n";
    ss.unsetf(std::ios::floatfield);
    str = ss.str();
    return str;
}

void Account::reset() {
    _id = 0;
    _balance = 0;
    _valid = false;
}

bool Account::deposit(const double &num) {
    if(!_valid || num <= 0)
        return false;
    _balance += num;
    return true;
}

bool Account::draw(const double &num) {
    if(!_valid || num > _balance - 0.01)
        return false;
    _balance -= num;
    return true;
}

int Account::get_total_account() {
    return _total_account;
}
