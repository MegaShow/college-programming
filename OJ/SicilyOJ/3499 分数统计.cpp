/* 3499 分数统计 */

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

int main(){
	int num, m, sum;
	cin >> num;
	for(int i = 0; i < num; i++){
		cin >> m;
		sum = 0;
		int var[m];
		for(int j = 0; j < m; j++)
			cin >> var[j];
		sort(var, var + m);
		for(int j = 1; j < m - 1; j++)
			sum += var[j];
		cout << setiosflags(ios::fixed) << setprecision(2) << static_cast<double> (sum) / (m - 2) << endl;
	}
	return 0;
}