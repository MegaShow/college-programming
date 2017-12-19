#define QUESTION 3


/* C002.cpp 输入一串数字，求和，读到1终止求和(求和不计1) */
#if QUESTION == 1
#include <iostream>
using namespace std;

int main(){
	int var, sum = 0;
	cin >> var;
	while(var != 1){
		sum += var;
		cin >> var;
	}
	cout << sum << endl;
	return 0;
}


/* C002.cpp 输入一串字符，输入这些字符，直到遇到!(!不输出) */
#elif QUESTION == 2
#include <iostream>
using namespace std;

int main(){
	char c;
	cin >> c;
	while(c != '!'){
		cout << c;
		cin >> c;
	}
	cout << endl;
	return 0;
}


/* C002.cpp 输入一串字符，直到遇到!(!不输出)，然后一起输出这些字符 */
#elif QUESTION == 3
#include <iostream>
using namespace std;

int main(){
	char c, str[1000];
	int top = -1;
	c = cin.get();
	while(c != '!'){
		top++;
		str[top] = c;
		c = cin.get();
	}
	str[top+1] = 0;
	cout << str << endl;
	return 0;
}

#endif