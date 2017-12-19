/* 3725 陶陶考试 */

#include <iostream>
using namespace std;

int main(){
	int num, max, var;
	cin >> num;
	while(num){
		for(int i = 0; i < num; i++){
			cin >> var;
			if(i == 0)
				max = var;
			else if(var > max)
				max = var;
		}
		cout << max << endl;
		cin >> num;
	}
	return 0;
}