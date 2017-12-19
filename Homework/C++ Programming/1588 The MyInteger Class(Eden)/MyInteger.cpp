#include <cmath>
#include "MyInteger.hpp"

MyInteger::MyInteger(int var){
  value = var;
}

int MyInteger::getValue() const{
  return value;
}

bool MyInteger::isEven() const{
  return (value & 1) == 0;
}
    
bool MyInteger::isOdd() const{
  return (value & 1) == 1;
}
    
bool MyInteger::isPrime() const{
  if(value == 1)
     return false;
  int sq = (int)sqrt(double(value));
  for(int i = 2; i <= sq; i++){
     if(value % i == 0)
           return false;
   }
  return true;
}

bool MyInteger::isEven(int var){
  return (var & 1) == 0;
}
    
bool MyInteger::isOdd(int var){
  return (var & 1) == 1;
}
    
bool MyInteger::isPrime(int var){
  if(var == 1)
     return false;
  int sq = (int)sqrt(double(var));
  for(int i = 2; i <= sq; i++){
     if(var % i == 0)
           return false;
   }
  return true;
}
    
bool MyInteger::isEven(const MyInteger& c){
  return c.isEven();
}

bool MyInteger::isOdd(const MyInteger& c){
  return c.isOdd();
}

bool MyInteger::isPrime(const MyInteger& c){
  return c.isPrime();
}

bool MyInteger::equals(int var){
  return value == var;
}

bool MyInteger::equals(const MyInteger& c){
  return value == c.value;
}

int MyInteger::parseInt(const std::string& s){
  int var = 0;
  for(int i = (s[0]=='-'?1:0); i < s.length(); i++){
     var = var * 10 + s[i] - '0';
   }
  if(s[0] == '-')
     return -var;
  return var;
}