#ifndef _USER_
#define _USER_

#include "Dress.hpp"
#include <vector>
#include <iostream>
using std::vector;
using std::pair;
using std::cout;

using std::endl;

using std::string;

class Mediator;
class User {
    private:
        string name;
        int money;
        int id;
        vector<Dress>dresses;
    public:
        int getId() const {return id;}
        static int Count;   // Assign to id
        User(const string & name, const int & money, const vector<pair<string, int> > & dresses);
        void BuyBeautifulDress(const int & id, const int & pay, const string & name);
        /*
            if pay > money
              cout << this->name << " : " << "Forget to Check Wallet!" << endl;
            if buy success
              cout << this->name << " : " << "So happy to get new Dress!" << endl;
            if No such a dress
              cout << this->name << " : " << "I'm so sorry maybe just because I love it so much." << endl;
            if Can't afford it
              cout << this->name << " : " <<  "OMG! Why it is so Expensive!" << endl;
        */
        void GetDressInfo(const int & id);
        /*
            You need print this sentence at first
            cout << this->name << " : " << "I wanna see your beautiful suits!" << endl;
        */
        pair<int, string> SellBeautifulDress(const int & pay, const string & dname);  // how to use to pair to represent diffierent information?
        /*
            if Don't have that dress
            cout << this->name <<" : " << "I never have this Dress stupid!" << endl;
            if pay is lower than your price
            cout << this->name << " : " <<  "No monry then no talking" << endl;
            if success
            cout << this->name << " : " << "What a good taste you have !" << endl;
        */
        void SendMessage(const int & to, const string & msg);
        void GetMessage(const string & msg);
        /*
            print like:
            cout << this->name <<" : I got a Msg - " << msg << endl;
        */
        void ShowMyCuteDresses();
        /*  
            print this at first:
            cout << this->name << " : ok,these are all I have : "<<endl;
            Then For each Dress
            cout << dresses[i].getName() << "-" << dresses[i].getPrice() << endl;
        */
};

#endif