// Mega Show
// [09] Alipay System 1 User(Eden)
#include <cctype>
#include "user.hpp"

namespace alipay{

inline bool User::verifyPasswordFormat(const std::string &password){
  if(password.length() < 8 || password.length() > 20)
     return false;
  for(int i = password.length()-1; i >= 0; i--){
     if(isalnum(password[i]) == false)
           return false;
   }
  return true;
}

inline bool User::verifyUsernameFormat(const std::string &username){
   if(username.length() < 6 || username.length() > 20)
       return false;
  for(int i = username.length()-1; i >= 0; i--){
     if(isalnum(username[i]) == false)
           return false;
   }
  return true;
}

inline bool User::verifyPhoneFormat(const std::string &phone){
  if(phone.length() != 13)
     return false;
  for(int i = phone.length()-1; i >= 0; i--){
     if(isdigit(phone[i]) == false)
           return false;
   }
  return true;
}

bool User::setUsername(const char *username){
  if(verifyUsernameFormat(std::string(username))){
     this->username = username;
     return true;
   }
   return false;
}

bool User::setPassword(const char *new_password, const char *old_password){
  if(this->password == std::string(old_password) && verifyPasswordFormat(std::string(new_password))){
     this->password = new_password;
     return true;
   }
  return false;
}

bool User::setPhone(const char *new_phone){
  if(verifyPhoneFormat(new_phone)){
     this->phone = new_phone;
     return true;
   }
  return false;
}

bool User::setGender(Gender::Gender gender){
  this->gender = gender;
  return true;
}

std::string User::getUsername(void){
  return this->username;
}

std::string User::getPhone(void){
  return this->phone;
}

alipay::Gender::Gender User::getGender(void){
  return this->gender;
}

// if passowrd is in correct, return -1
long long int User::getMoneyAmount(const char *password){
  if(this->password == std::string(password))
     return this->balance;
  return -1;
}

bool User::deposit(long long int amount){
  if(amount > 0){
     this->balance += amount;
     return true;
   }
  return false;
}

bool User::withdraw(long long int amount, const char *password){
  if(this->password == std::string(password) && amount <= this->balance && amount > 0){
     this->balance -= amount;
     return true;
   }
  return false;
}

}
