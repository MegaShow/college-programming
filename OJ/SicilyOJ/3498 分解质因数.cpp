/* 3498 分解质因数 */

#include <iostream>
using namespace std;

int main(){
	int num, var, out;
	cin >> num;
	for(int i = 0; i < num; i++){
		cin >> var;
		out = 2;
		while(out <= var){
			if(var % out == 0){
				var /= out;
				cout << out << " ";
			}
			else
				out++;
		}
		cout << endl;
	}
	return 0;
}