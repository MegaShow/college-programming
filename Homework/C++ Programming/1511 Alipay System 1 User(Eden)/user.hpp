// Written by Matrix
#include <string>

#ifndef USER_H_
#define USER_H_

namespace alipay {

namespace Gender {
enum Gender { Female = 0, Male = 1, Unknown = 2 };
}

class User {
  std::string username;
  std::string password;
  std::string phone;
  Gender::Gender gender;
  long long int balance;

  inline bool verifyPasswordFormat(const std::string &password);
  inline bool verifyUsernameFormat(const std::string &username);
  inline bool verifyPhoneFormat(const std::string &phone);

 public:
  User() {
    this->gender = Gender::Unknown;
    this->balance = 0;
  }

  bool setUsername(const char *username);
  bool setPassword(const char *new_password, const char *old_password);
  bool setPhone(const char *new_phone);
  bool setGender(Gender::Gender gender);

  std::string getUsername(void);
  std::string getPhone(void);
  alipay::Gender::Gender getGender(void);

  // if passowrd is in correct, return -1
  long long int getMoneyAmount(const char *password);
  bool deposit(long long int amount);
  bool withdraw(long long int amount, const char *password);
};
}

#endif  // USER_H_
 
