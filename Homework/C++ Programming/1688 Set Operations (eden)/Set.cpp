// MegaShow
#include "Set.hpp"
    

Set::Set(){
    size = 0;
}

    // Create an set with some element.
Set::Set(int* m, int s){
    for(int i = 0; i < s; i++)
        members[i] = m[i];
    size = s;
}
    
    // Copy Constructor
Set::Set(Set const &s){
    size = 0;
    for(int i = 0; i < s.size; i++)
        append(s.members[i]);
}
    
    // append a element to set.
    // If element in the set, return false.
    // Or insert in set and return true.
bool Set::append(int e){
    for(int i = 0; i < size; i++){
        if(members[i] == e)
            return false;
    }
    members[size++] = e;
    return true;
}
    
    // remove a element by its value from set.
    // If element in the set, then remove it and return true.
    // Or return false.
bool Set::remove(int e){
    for(int i = 0; i < size; i++){
        if(members[i] == e){
            for(int j = i; j < size - 1; j++)
                members[j] = members[j+1];
            size--;
            return true;
        }
    }
    return false;
}
    
    // return true if the set is empty, or return false.
bool Set::isEmptySet(){
    return size == 0;
}
    
    // return true if the element e is in the set, or return false.
bool Set::isInSet(int e){
    for(int i = 0; i < size; i++){
        if(members[i] == e)
            return true;
    }
    return false;
}
    
    // & is intersection of two set
Set Set::operator&(const Set &s){
    Set tmp;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < s.size; j++){
            if(members[i] == s.members[j])
                tmp.append(members[i]);
        }
    }
    return tmp;
}
    
    // | is union of two set
Set Set::operator|(const Set &s){
    Set tmp;
    for(int i = 0; i < size; i++)
        tmp.append(members[i]);
    for(int i = 0; i < s.size; i++)
        tmp.append(s.members[i]);
    return tmp;
}
    
    // A - B is the complement of B with respect to A
Set Set::operator-(const Set &s){
    Set tmp;
    for(int i = 0; i < size; i++){
        bool flag = false;
        for(int j = 0; j < s.size; j++){
            if(members[i] == s.members[j])
                flag = true;
        }
        if(flag == false)
            tmp.append(members[i]);
    }
    return tmp;
}

    // A + B is their symmetric difference. A + B = (A - B) | (B - A)
Set Set::operator+(const Set &s){
    Set a(members, size);
    Set b = s;
    return (a - b) | (b - a);
}
    
    // return set.
int* Set::getMembers(){
    return members;
}
    
    // return size of set.
int Set::getSize(){
    return size;
}