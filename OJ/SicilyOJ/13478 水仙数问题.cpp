/* 13478 水仙数问题 */

#include <iostream>
using namespace std;

int main(){
	int num;
	cin >> num;
	for(int i = 1; i <= 9; i++)
		for(int j = 0; j <= 9; j++)
			for(int k = 0; k <= 9; k++){
				if(i * 100 + j * 10 + k == i * i * i + j * j * j + k * k * k)
					cout << i * 100 + j * 10 + k << endl;
				if(i * 100 + j * 10 + k == num)
					return 0;
			}
	return 0;
}