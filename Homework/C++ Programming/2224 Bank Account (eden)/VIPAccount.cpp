// MegaShow
#include <sstream>
#include <string>
#include "VIPAccount.h"

int VIPAccount::_total_vip_account = 0;
int VIPAccount::_acc_id_ptr = 12050000;

VIPAccount::VIPAccount() {
    reset();
    _id = _acc_id_ptr;
    _acc_id_ptr++;
    _total_vip_account++;
}

VIPAccount::~VIPAccount() {
    _total_vip_account--;
}

bool VIPAccount::loan(const double &num) {
    if(_loan + num > _loan_limit || num <= 0)
        return false;
    _loan += num;
    deposit(num);
    return true;
}

bool VIPAccount::repay(const double &num) {
    if(num > _loan || num <= 0)
        return false;
    _loan -= num;
    draw(num);
    if(_loan < 0) {
        deposit(-_loan);
        _loan = 0;
    }
    return true;
}

// override
std::string VIPAccount::profile() const {
    std::stringstream ss;
    std::string str;
    ss << "ID:" << _id << "\nBALANCE:";
    ss.precision(6);
    ss.setf(std::ios::fixed, std::ios::floatfield);
    ss << _balance << "\nVALID:Y\nTYPE:VIP\nLOAN:" << _loan << ",LIMIT:" << _loan_limit << "\n";
    ss.unsetf(std::ios::floatfield);
    str = ss.str();
    return str;
}

void VIPAccount::reset() {
    _balance = 10;
    _valid = true;
    _loan = 0;
    _loan_limit = 1000;
}

// static
int VIPAccount::get_total_vip_account() {
    return _total_vip_account;
}