// MegaShow
#include <cstdio>
#include "global.hpp"
#include "user.hpp"

namespace Alipay{

user::user(const char* username, const char* password){
    snprintf(this->username, 21, username);
    snprintf(this->password, 21, password);
    balance = 0;
}

user::~user(){}

const char* user::getUsername() const{
    return username;
}

const char* user::getPassword() const{
    return password;
}

const void user::setUsername(const char* username){
    snprintf(this->username, 21, username);
}

const void user::setPassword(const char* password){
    snprintf(this->password, 21, password);
}

double user::getBalance(){
    return balance;
}

bool user::withdraw(double amount){
    if(amount <= 0 || (amount - balance) >= PRECISION)
        return false;
    balance -= amount;
    return true;
}

bool user::deposite(double amount){
    if(amount <= 0)
        return false;
    balance += amount;
    return true;
}

}