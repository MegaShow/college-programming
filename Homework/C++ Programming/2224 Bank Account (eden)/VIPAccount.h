#ifndef VIP_ACCOUNT_H_
#define VIP_ACCOUNT_H_
 
#include "Account.h"
 
class VIPAccount : public Account {
  private:
    static int _total_vip_account;
    static int _acc_id_ptr;
  protected:
    double _loan;
    double _loan_limit;  // initial as 1k
  public:
    VIPAccount();
    ~VIPAccount();
    bool loan(const double &num);
    bool repay(const double &num);
    // override
    std::string profile() const;
    void reset();
    // static
    static int get_total_vip_account();
};
 
#endif
