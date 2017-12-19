/* 4086 韩信点兵 */

#include <iostream>
using namespace std;

int main(){
	int num, p3, p5, p7, var;
	cin >> num;
	for(int i = 0; i < num; i++){
		cin >> p3 >> p5 >> p7;
		var = 10 + p5;
		while(var % 7 != p7)
			var += 5;
		while(var % 3 != p3)
			var += 5 * 7;
		if(var > 100)
			cout << "No answer" << endl;
		else
			cout << var << endl;
	}
}