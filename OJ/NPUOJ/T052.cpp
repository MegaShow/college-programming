/*
 *	Name: [T052] 字符串
 *	Author: Mega Chan
 *	Date: 2016.11.14 19:47
 */

#include <iostream>
#include <cstring>
using namespace std;

int main(){
	int top = -1, num = 0;
	char str[1000], out[1000];
	cin.getline(str,999);
	int len = strlen(str);
	for(int i = 0; i < len; i++){
		if(str[i] >= '0' and str[i] <= '9'){
			num++;
			if(top != -1){
				top++;
				out[top] = ' ';
			}
			for(int j = i; str[j] >= '0' and str[j] <= '9'; j++){
				top++;
				out[top] = str[j];
				i = j;
			}
		}
	}
	cout << num << endl;
	for(int i = 0; i <= top; i++)
		cout << out[i];
	cout << endl;
	return 0;
}