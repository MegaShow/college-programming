// MegaShow
#include <sstream>
#include <cstring>
#include "userController.hpp"

namespace Alipay{

int userController::getUserIndex(const char* username) const{
    for(int i = 0; i < usercount; i++){
        if(strcmp(users[i]->getUsername(), username) == 0)
            return i;
    }
    return -1;
}
 
userController::userController(double interest_rate){
    usercount = 0;
    this->interest_rate = interest_rate;
}

userController::~userController(){
    for(int i = 0; i < usercount; i++)
        delete users[i];
}

bool userController::createUser(const char* username, const char* password){
    if(getUserIndex(username) != -1)
        return false;
    if(std::string(password).length() < 8)
        return false;
    users[usercount++] = new user(username, password);
    return true;
}

bool userController::deposite(const char* username, double amount){
    int index = getUserIndex(username);
    if(index == -1)
        return false;
    return users[index]->deposite(amount);
}

bool userController::withdraw(const char* username, double amount){
    int index = getUserIndex(username);
    if(index == -1)
        return false;
    return users[index]->withdraw(amount);
}

std::string userController::getUserInfoByName(const char* username) const{
    int index = getUserIndex(username);
    if(index == -1)
        return "username:\npassword:\nbalance:\n";
    std::string str = "username:";
    str += username;
    str += "\npassword:*********\nbalance:";
    std::stringstream ss;
    std::string tmp;
    ss << users[index]->getBalance();
    ss >> tmp;
    str += tmp;
    return str;
}

int userController::getUserCount(void) const{
    return usercount;
}

bool userController::removeUserByUsername(const char* username){
    int index = getUserIndex(username);
    if(index == -1)
        return false;
    delete users[index];
    usercount--;
    for(int i = index; i < usercount; i++)
        users[i] = users[i+1];
    return true;
}

bool userController::setInterest(double interest){
    if(interest <= 0 || interest >= 1)
        return false;
    interest_rate = interest;
    return true;
}

void userController::payInterest(void){
    for(int i = 0; i < usercount; i++){
        users[i]->deposite(users[i]->getBalance() * interest_rate);
    }
}

}