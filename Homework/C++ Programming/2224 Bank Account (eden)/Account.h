#ifndef SSCPP2014_ACCOUNT_H
#define SSCPP2014_ACCOUNT_H
 #include <string>
 class Account {
  protected:
    int _id;
    double _balance;
    bool _valid;
    static int _total_account;
  public:
    Account();
    ~Account();
    int id() const;
    double balance() const;
    bool valid() const;
    std::string profile() const;
    void reset();
    bool deposit(const double &num);
    bool draw(const double &num);
    static int get_total_account();
};
 #endif
 