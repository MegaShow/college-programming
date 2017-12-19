// ST054

#include <iostream>

using namespace std;

int main(){
	char str[1000];
	int top = 0;
	str[0] = cin.get();
	while(str[top] != '='){
		top++;
		str[top] = cin.get();
	}
	for(int i = top - 1; i >= 0; i--)
		cout << str[i];
	cout << endl;
	return 0;
}

