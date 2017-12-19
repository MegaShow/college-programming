// MegaShow
#include <sstream>
#include <string>
#include "PersonalAccount.h"

int PersonalAccount::_total_per_account = 0;
int PersonalAccount::_acc_id_ptr = 12010000;

PersonalAccount::PersonalAccount() {
    reset();
    _id = _acc_id_ptr;
    _acc_id_ptr++;
    _total_per_account++;
}

PersonalAccount::~PersonalAccount() {
    _total_per_account--;
}

// override
std::string PersonalAccount::profile() const {
    std::stringstream ss;
    std::string str;
    ss << "ID:" << _id << "\nBALANCE:";
    ss.precision(6);
    ss.setf(std::ios::fixed, std::ios::floatfield);
    ss << _balance << "\nVALID:Y\nTYPE:PERSONAL\n";
    ss.unsetf(std::ios::floatfield);
    str = ss.str();
    return str;
}

void PersonalAccount::reset() {
    _balance = 10;
    _valid = true;
}

// static
int PersonalAccount::get_total_per_account() {
    return _total_per_account;
}