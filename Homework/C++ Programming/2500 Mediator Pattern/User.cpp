// MegaShow
#include "Mediator.hpp"
#include "User.hpp"
using std::make_pair;

int User::Count = 0;

User::User(const string &name, const int &money, const vector<pair<string, int> > &dresses)
        : id(Count), name(name), money(money) {
    Count++;
    for(int i = 0; i < dresses.size(); i++) {
        this->dresses.push_back(Dress(dresses[i].first, dresses[i].second));
    }
}


void User::BuyBeautifulDress(const int &id, const int &pay, const string &name) {
    if(pay > money) {
        cout << this->name << " : " << "Forget to Check Wallet!" << endl;
    }
    else {
        Mediator* mediator = Mediator::getInstance();
        pair<int, string> n = mediator->TradeHandler(id, pay, name);
        if(n.second.size() == 0 && n.first == 0) {
            cout << this->name << " : " << "I'm so sorry maybe just because I love it so much." << endl;
        }
        else if(n.second.size() == 0) {
            cout << this->name << " : " <<  "OMG! Why it is so Expensive!" << endl;
        }
        else {
            cout << this->name << " : " << "So happy to get new Dress!" << endl;
            money -= pay;
            dresses.push_back(Dress(n.second, n.first));
        }
    }
}


void User::GetDressInfo(const int &id) {
    cout << this->name << " : " << "I wanna see your beautiful suits!" << endl;
    Mediator* mediator = Mediator::getInstance();
    mediator->DressInfoHandler(id);
}


pair<int, string> User::SellBeautifulDress(const int &pay, const string &dname) {
    vector<Dress>::iterator it = dresses.begin();
    while(it != dresses.end() && it->getName() != dname) {
        it++;
    }
    if(it == dresses.end()) {
        cout << this->name <<" : " << "I never have this Dress stupid!" << endl;
        return make_pair(0, "");
    }
    else if(it->getPrice() > pay) {
        cout << this->name << " : " <<  "No monry then no talking" << endl;
        return make_pair(1, "");
    }
    cout << this->name << " : " << "What a good taste you have !" << endl;
    pair<int, string> s = make_pair(it->getPrice(), it->getName());
    dresses.erase(it);
    money += pay;
    return s;
}


void User::SendMessage(const int &to, const string &msg) {
    Mediator* mediator = Mediator::getInstance();
    mediator->ChatHandler(to, msg);
}


void User::GetMessage(const string &msg) {
    cout << this->name <<" : I got a Msg - " << msg << endl;
}


void User::ShowMyCuteDresses() {
    cout << this->name << " : ok,these are all I have : "<<endl;
    for(int i = 0; i < dresses.size(); i++) {
        cout << dresses[i].getName() << "-" << dresses[i].getPrice() << endl;
    }
}
