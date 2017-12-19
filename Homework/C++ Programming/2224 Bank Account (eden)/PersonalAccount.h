#ifndef PERSONAL_ACCOUNT_H_
#define PERSONAL_ACCOUNT_H_
 
#include "Account.h"
 
class PersonalAccount : public Account {
  private:
    static int _total_per_account;
    static int _acc_id_ptr;
  public:
    PersonalAccount();
    ~PersonalAccount();
    // override
    std::string profile() const;
    void reset();
    // static
    static int get_total_per_account();
};
 
#endif