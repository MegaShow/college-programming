/* 3497 水仙花数 */

#include <iostream>
#include <cmath>
using namespace std;

int main(){
	for(int num = 100; num < 1000; num++){
		int sum = 0, var = num;
		while(var){
			sum += pow(var % 10, 3);
			var /= 10;
		}
		if(sum == num)
			cout << num << endl;
	}
	return 0;
}