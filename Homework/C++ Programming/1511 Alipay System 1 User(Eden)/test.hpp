// Written by Matrix
#ifndef TEST_H_
#define TEST_H_
#include "user.hpp"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::string;

namespace unittest {
class TEST {
 public:
  // complete legal operations
  void TestCase1() {
    cout << "Test1" << endl;
    alipay::User u;

    char username[20];
    cin >> username;
    u.setUsername(username) ? cout << "Pass" : cout << "Fail";
    cout << "\tsetting a legal username." << username << endl;

    char password[20];
    cin >> password;
    u.setPassword(password, "") ? cout << "Pass" : cout << "Fail";
    cout << "\tsetting a legal password for a blank password." << password
         << endl;

    char phone[20];
    cin >> phone;
    u.setPhone(phone) ? cout << "Pass" : cout << "Fail";
    cout << "\tsetting a legal phone." << phone << endl;

    int gender;
    cin >> gender;
    u.setGender(gender == 0 ? alipay::Gender::Female : alipay::Gender::Male)
        ? cout << "Pass"
        : cout << "Fail";
    cout << "\tsetting a legal gender: " << (gender == 0 ? "Female." : "Male.")
         << endl;

    string username_s = u.getUsername();
    username_s == username ? cout << "Pass" : cout << "Fail";
    cout << "\tusername should be equal: (" << username << "," << username_s
         << ")." << endl;

    string phone_s = u.getPhone();
    phone == phone_s ? cout << "Pass" : cout << "Fail";
    cout << "\tphone should be equal: (" << phone << "," << phone_s << ")."
         << endl;

    int money;
    cin >> money;
    u.deposit(money) ? cout << "Pass" : cout << "Fail";
    cout << "\ttry to deposit." << endl;

    cin >> money;
    u.withdraw(money, password) ? cout << "Pass" : cout << "Fail";
    cout << "\ttry to withdraw." << endl;

    cout << endl;
  }

  // complete illegal operations
  void TestCase2() {
    cout << "Test2" << endl;
    alipay::User u;

    char wrong_username[20];
    cin >> wrong_username;
    !u.setUsername(wrong_username) ? cout << "Pass" : cout << "Fail";
    cout << "\tsetting an illegal username." << wrong_username << endl;

    char wrong_phone[20];
    cin >> wrong_phone;
    !u.setPhone(wrong_phone) ? cout << "Pass" : cout << "Fail";
    cout << "\tsetting an illegal phone." << wrong_phone << endl;

    char wrong_password[20];
    cin >> wrong_password;
    !u.setPassword(wrong_password, "") ? cout << "Pass" : cout << "Fail";
    cout << "\tsetting an illegal password." << wrong_password << endl;

    u.setPassword("20482048123", "");

    !u.setPassword("123", "123") ? cout << "Pass" : cout << "Fail";
    cout << "\tsetting a new password using wrong old password." << endl;

    cout << endl;
  }

  // complete illegal operations2
  void TestCase3() {
    cout << "Test3" << endl;
    alipay::User u;

    u.setPassword("123456789", "");

    !u.withdraw(-1000, "123456789") ? cout << "Pass" : cout << "Fail";
    cout << "\ttry to cheat money using negative number." << endl;

    u.deposit(1000);
    !u.withdraw(10000, "123456789") ? cout << "Pass" : cout << "Fail";
    cout << "\ttry to cheat money using loan which is not supported." << endl;

    cout << endl;
  }

  void runAllCases() {
    TestCase1();
    TestCase2();
    TestCase3();
  }
};
}

#endif  // TEST_H_
