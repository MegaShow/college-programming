/* 1003 Displaying patterns */

#include <iostream>
#include <iomanip>
using namespace std;

void displayPattern(int n){
	cout << right;
	for(int i = 1; i <= n; i++){
		cout << setw(3*(n-i+1)) << i;
		for(int j = i - 1; j >= 1; j--){
			cout << setw(3) << j;
		}
		cout << endl;
	}
}

/* test */
int main(){
	displayPattern(7);
}
/* end of test */