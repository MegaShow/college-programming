/* 3912 计算星期几 */

#include <iostream>
using namespace std;

int DayNum[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
char DayName[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int main(){
	int num, month, day, var;
	cin >> num;
	for(int i = 0; i < num; i++){
		cin >> month >> day;
		for(int j = 0; j < month - 1; j++)
			day += DayNum[j];
		cout << DayName[(day + 5) % 7] << endl;
	}
	return 0;
}