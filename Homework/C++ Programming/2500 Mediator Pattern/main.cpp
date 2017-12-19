#include "Mediator.hpp"

#include <iostream>
using std::cin;
int main() {
    cout << "Generate User" << endl;
    vector<User*> users;
    int size;
    cin >> size;
    while (size--) {
        string name;
        int money;
        vector<pair<string,int> > dresses;
        cin >> name >> money;
        int dress_size;
        cin >> dress_size;
        while (dress_size--) {
            string dname;
            int price;
            cin >> dname >> price;
            dresses.push_back(std::make_pair(dname, price));
        }
        User* t = new User(name, money, dresses);
        users.push_back(t);
        Mediator::getInstance()->RegisterHandler(t);
    }
    cout << "Communication part Start!" << endl;
    int Userid;
    while (cin >> Userid && Userid != -1) {
        char c;
        cin >> c;
        switch(c) {
            case 'b': {
                    string dname;
                    int pay, seller;
                    cin >> dname >> pay >>seller;
                    users[Userid]->BuyBeautifulDress(seller, pay, dname);
                    break;
                    }
            case 'd': {
                    int id;
                    cin >> id;
                    users[Userid]->GetDressInfo(id);
                    break;
                    }
            case 's': {
                    int to;
                    string msg;
                    cin >> to;
                    getline(cin, msg,'\n');
                    users[Userid]->SendMessage(to, msg);
                    break;
                    }
                default:
                    break;
            }
    }
    for (int i = 0; i < users.size(); i++)
        delete users[i];
    Mediator::DestroyIns();
    return 0;
}