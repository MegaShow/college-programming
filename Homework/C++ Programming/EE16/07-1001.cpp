/* 1001 Displaying an integer reversed */

#include <iostream>
using namespace std;

void reverse(int var){
	if(var < 0){
		cout << "-";
		var = -var;
	}
	else if(var == 0){
		cout << "0";
		return;
	}
	while(var){
		cout << var % 10;
		var /= 10;
	}
}

/* test */
int main(){
	reverse(-6543);
	reverse(0);
}
/* end of test */