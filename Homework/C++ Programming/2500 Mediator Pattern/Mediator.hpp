#ifndef _MEDIATOR_
#define _MEDIATOR_
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)
#include <list>
#include <iostream>
#include "User.hpp"
using std::list;
class Mediator {
    private:
        DISALLOW_COPY_AND_ASSIGN(Mediator);
        std::list<User*> users;
        Mediator() {}
        ~Mediator() {}
        static Mediator* Ins;
    public:
        static Mediator* getInstance() {
            return Mediator::Ins == NULL ? (Mediator::Ins = new Mediator()) : Mediator::Ins;
        }
        static void DestroyIns() {
            if (Ins)
                delete Ins;
            Ins = NULL;
        }
        void RegisterHandler(User * u);
        void ChatHandler(const int & to, const string & msg);
        /*
            if No Such a User
            cout << "Are you kidding ? There is no such a guy!" << endl;
        */
        pair<int,string> TradeHandler(const int & to, const int & pay, const string & dressName);
        /*
            if no such a User
            cout << "There is no Such a guy!" << endl;
        */
        void DressInfoHandler(const int & to);
};


#endif