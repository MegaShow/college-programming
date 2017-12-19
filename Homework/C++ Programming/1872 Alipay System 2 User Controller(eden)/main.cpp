#include "userController.hpp"
#include <iostream>
#include <string>
 
using std::cin;
using std::cout;
using std::endl;
using std::string;
 
void help() {
  cout << "Welcome to Alipay Managament System" << endl;
  cout << "Please select your service using the number:" << endl;
  cout << "[1] Create an user" << endl;
  cout << "[2] Get an user's info by username" << endl;
  cout << "[3] Get total user count" << endl;
  cout << "[4] Remove one user" << endl;
  cout << "[5] Set interest" << endl;
  cout << "[6] Pay interest" << endl;
  cout << "[7] withdraw(for one account)" << endl;
  cout << "[8] deposite(for one account)" << endl;
  cout << "[9] Display help info" << endl;
  cout << "[0] Quit" << endl;
}
 
int main() {
  help();
  Alipay::userController controller(0.005);
  while (true) {
    cout << "Alipay $ ";
    int choose;
    cin >> choose;
    switch (choose) {
      case 1:
        if (true) {
          char username[21];
          char password[21];
          cout << "please input [username] [password]" << endl;
          cin >> username >> password;
          if (controller.createUser(username, password)) {
            cout << "create user successfully!" << endl;
          } else {
            cout << "fail to create user with username:" << username
                 << " password:" << password << endl;
          }
          break;
        }
      case 2:
        if (true) {
          char username[21];
          cout << "please input username" << endl;
          cin >> username;
          cout << "user info:" << endl;
          cout << controller.getUserInfoByName(username) << endl;
          break;
        }
      case 3:
        cout << "Total user count: " << controller.getUserCount() << endl;
        break;
      case 4:
        if (true) {
          char username[21];
          cout << "please input username" << endl;
          cin >> username;
          if (controller.removeUserByUsername(username)) {
            cout << "remove user successfully!" << endl;
          } else {
            cout << "fail to reomove user with username:" << username << endl;
          }
          break;
        }
      case 5:
        if (true) {
          double newRate;
          cout << "please input the new interest rate:" << endl;
          cin >> newRate;
          if (controller.setInterest(newRate)) {
            cout << "set interest successfully" << endl;
          } else {
            cout << "set interest falied with interest rate:" << newRate
                 << endl;
          }
          break;
        }
      case 6:
        if (true) {
          controller.payInterest();
          cout << "pay interest compelete" << endl;
          break;
        }
      case 7:
        if (true) {
          cout << "please input [username] [withdraw_amount]" << endl;
          char username[21];
          double amount;
          cin >> username >> amount;
          if (controller.withdraw(username, amount)) {
            cout << "withdraw successfully!" << endl;
          } else {
            cout << "withdraw falied with amount:" << amount << endl;
          }
          break;
        }
      case 8:
        if (true) {
          cout << "please input [username] [deposite_amount]" << endl;
          char username[21];
          double amount;
          cin >> username >> amount;
          if (controller.deposite(username, amount)) {
            cout << "deposite successfully!" << endl;
          } else {
            cout << "deposite falied with amount:" << amount << endl;
          }
          break;
        }
      case 0:
        cout << "Tanks for using Alipay, Bye!" << endl;
        return 0;
      case 9:
        help();
        break;
      default:
        cout << "No suchu command! Please input again" << endl;
        help();
    }
  }
 
  return 0;
}
 