// MegaShow
#include "Mediator.hpp"

Mediator* Mediator::Ins = NULL;

void Mediator::RegisterHandler(User *u) {
    users.push_back(u);
}

void Mediator::ChatHandler(const int &to, const string &msg) {
    list<User*>::iterator it = users.begin();
    while(it != users.end() && (*it)->getId() != to) {
        it++;
    }
    if(it == users.end()) {
        cout << "Are you kidding ? There is no such a guy!" << endl;
    }
    (*it)->GetMessage(msg);
}
/*
            if No Such a User
            cout << "Are you kidding ? There is no such a guy!" << endl;
        */
pair<int, string> Mediator::TradeHandler(const int &to, const int &pay, const string &dressName) {
    list<User*>::iterator it = users.begin();
    while(it != users.end() && (*it)->getId() != to) {
        it++;
    }
    if(it == users.end()) {
        cout << "Are you kidding ? There is no such a guy!" << endl;
    }
    return (*it)->SellBeautifulDress(pay, dressName);
}
/*
            if no such a User
            cout << "There is no Such a guy!" << endl;
        */
void Mediator::DressInfoHandler(const int &to) {
    list<User*>::iterator it = users.begin();
    while(it != users.end() && (*it)->getId() != to) {
        it++;
    }
    if(it == users.end()) {
        cout << "There is no Such a guy!" << endl;
        return;
    }
    (*it)->ShowMyCuteDresses();
}