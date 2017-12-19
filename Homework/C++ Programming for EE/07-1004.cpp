/* 1004 Displaying characters */

#include <iostream>
using namespace std;

void printChars(char ch1, char ch2, int numberPerLine){
	int index = 0;
	for(char str = ch1; str <= ch2; str++){
		cout << str;
		index++;
		if(index == numberPerLine){
			cout << endl;
			index = 0;
		}
	}
}

/* test */
int main(){
	printChars('1', 'D', 10);
}
/* end of test */