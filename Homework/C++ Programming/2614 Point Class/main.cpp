#include"Point.h"
#include<iostream>
using namespace std;

int main(){
 int n,m;
 cin>>n;
 int *temp1 = new int [n];
 for(int i = 0 ; i < n ; i++)
  cin>>temp1[i];
 Point a(temp1,n);
 a.print();
 cin>>m;
 int *temp2 = new int [m];
 for(int i = 0 ; i < m ; i++)
  cin>>temp2[i];
 Point b(temp2,m); 
 b.print();
 delete []temp1;
 delete []temp2;


 (a+b).print();
 Point c = a-b;
 c.print();
 return 0;
}
