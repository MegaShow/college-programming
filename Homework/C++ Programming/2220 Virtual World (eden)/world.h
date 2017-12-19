// MegaShow
#ifndef WORLD_H_
#define WORLD_H_

#include <iostream>
#include <set>
#include <map>
#include <algorithm>

struct person {
    static int num;
    const int id;
    person() :id(num) {
        num++;
    }
};

int person::num = 0;



class group {
private:
    int type;
    std::map<int, std::set<int> > member;
public:
    group(int _type) :type(_type) {}
    
    void displayGroup() {
        std::map<int, std::set<int> >::iterator it;
        for(it = member.begin(); it != member.end(); it++) {
            std::cout << "Person_" << it->first << ":";
            std::set<int>::iterator init = it->second.begin();
            if(init != it->second.end()) {
                std::cout << " " << *init;
                init++;
            }
            else {
                std::cout << " null";
            }
            while(init != it->second.end()) {
                std::cout << ", " << *init;
                init++;
            }
            std::cout << std::endl;
        }
    }

    bool addMember(person &p) {
        std::set<int> pset;
        if(type) {
            std::map<int, std::set<int> >::iterator it;
            for(it = member.begin(); it != member.end(); it++) {
                pset.insert(it->first);
                it->second.insert(p.id);
            }
        }
        //member[p.id] = *p;
        std::pair<std::map<int, std::set<int> >::iterator, bool> ret = 
            member.insert(std::map<int, std::set<int> >::value_type(p.id, pset));
        return ret.second;
    }

    bool deleteMember(person &p) {
        return member.erase(p.id);
    }

    bool makeFriend(person &p1, person &p2) {
        if(member[p1.id].find(p2.id) != member[p1.id].end())
            return false;
        member[p1.id].insert(p2.id);
        member[p2.id].insert(p1.id);
        return true;
    }

    bool breakRelation(person &p1, person &p2) {
        if(member[p1.id].find(p2.id) == member[p1.id].end())
            return false;
        member[p1.id].erase(p2.id);
        member[p2.id].erase(p1.id);
        return true;
    }
};

#endif