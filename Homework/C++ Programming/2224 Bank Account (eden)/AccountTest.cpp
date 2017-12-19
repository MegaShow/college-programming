#include <iostream>
#include "Account.h"
#include "PersonalAccount.h"
#include "VIPAccount.h"
using namespace std;
 
void display_count() {
  cout << Account::get_total_account() << ",";
  cout << PersonalAccount::get_total_per_account() << ",";
  cout << VIPAccount::get_total_vip_account() << endl;
}
 
int main() {
  display_count();
  if (true) {
    Account a0, a1, a2;
    display_count();
    PersonalAccount b0, b1;
    display_count();
  }
  VIPAccount c0, c1, c2, c3;
  display_count();
 
  Account *bptr = new Account();
  cout << bptr->profile() << endl;
  cout << bptr->id() << bptr->balance() << bptr->valid() << endl;
  delete bptr;
 
  PersonalAccount *pptr = new PersonalAccount();
  cout << pptr->profile() << endl;
  for (int i = 0; i < 5; ++i) {
    double t;
    int op;
    cin >> op >> t;
    if (op < 5) {
      cout << pptr->deposit(t) << ", ";
    } else {
      cout << pptr->draw(t) << ", ";
    }
    cout << pptr->balance() << endl;
  }
  cout << pptr->profile() << endl;
  pptr->reset();
  cout << pptr->profile() << endl;
  delete pptr;
 
  VIPAccount *vptr = new VIPAccount();
  cout << vptr->profile() << endl;
  for (int i = 0; i < 5; ++i) {
    double t;
    int op;
    cin >> op >> t;
    if (op < 5) {
      cout << vptr->loan(t);
    } else {
      cout << vptr->repay(t);
    }
    cout << "\n" << vptr->profile() << endl;
  }
  vptr->reset();
  cout << vptr->profile() << endl;
  delete vptr;
 
  return 0;
}
