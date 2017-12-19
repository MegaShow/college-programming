/* 1766 火柴棒等式 */
/* NOIP 2008 */

#include <iostream>
using namespace std;

int arr[10] = {6,2,5,5,4,5,6,3,7,6};

int getvar(int num){
	if(num == 0)
		return arr[0];
	int sum = 0;
	while(num){
		sum += arr[num % 10];
		num /= 10;
	}
	return sum;
}

int main(){
	int var, sum;
	while(cin >> var){
		var -= 4;
		sum = 0;
		for(int i = 0; i < 1000; i++)
			for(int j = 0; j < 1000; j++)
				if(getvar(i) + getvar(j) + getvar(i+j) == var)
					sum++;
		cout << sum << endl;
	}
}