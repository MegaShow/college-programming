/* 3718 批改作业 */

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

int main(){
	int people, work, var, sum, num = 0;
	cin >> people >> work;
	for(int i = 0; i < people; i++){
		sum = 0;
		for(int j = 0; j < work; j++){
			cin >> var;
			sum += var;
		}
		cout << setiosflags(ios::fixed) << setprecision(2) << static_cast<double>(sum) / work << endl;
		if(sum < work * 60)
			num++;
	}
	cout << num << endl;
}