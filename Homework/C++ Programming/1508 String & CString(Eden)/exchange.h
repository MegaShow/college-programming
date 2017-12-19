// MegaShow
// [07] String & CString(Eden)
#ifndef EXCHANGE_H_
#define EXCHANGE_H_

#include <string>


std::string change1(char* st){
  return std::string(st);
}

void change2(std::string st1, char* st2){
  for(int i = 0; i <= st1.length(); i++)
     st2[i] = st1[i];
}

#endif
