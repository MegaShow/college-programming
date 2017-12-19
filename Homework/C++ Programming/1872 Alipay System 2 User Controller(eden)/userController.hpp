#ifndef ALIPAY_USERCONTROLLER_H
 
#include "user.hpp"
#include <string>
#include "global.hpp"
 
namespace Alipay {
class userController {
 private:
  double interest_rate;
  user* users[MAX_USER];
  int usercount;
  int getUserIndex(const char* username) const;
 
 public:
  userController(double interest_rate);
  ~userController();
  bool createUser(const char* username, const char* password);
  bool deposite(const char* username, double amount);
  bool withdraw(const char* username, double amount);
  std::string getUserInfoByName(const char* username) const;
  int getUserCount(void) const;
  bool removeUserByUsername(const char* username);
  bool setInterest(double interest);
  void payInterest(void);
};
}
 
#endif  // !ALIPAY_USERCONTROLLER_H