/* 3913 阶乘之和 */

#include <iostream>
using namespace std;

int factorial(int n){
	if(n >= 30)     // 大于等于30最后六位皆为0
		return 0;
	if(n == 1)
		return 1;
	return n * factorial(n - 1) % 1000000;
}

int main(){
	int var, sum = 0;
	cin >> var;
	for(int i = 1; i <= var; i++)
		sum = ( sum + factorial(i) ) % 1000000;
	cout << sum << endl;
	return 0;
}