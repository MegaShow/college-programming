/*
 *	Name: [031] Basic Number Reading
 *	Author: Mega Chan
 *	Date: 2016.11.19 13:26
 */
 
#include <stdio.h>
#include <string.h>

char temp[20];

char* reverse(char* str){
	int len = strlen(str);
	temp[len] = 0;
	for(int i = 0; i < len; i++)
		temp[i] = str[len-i-1];
	return temp;
}

int base_to_10(char* str, int base){
	int sum = 0;
	for(int i = 0; str[i] != 0; i++)
		sum = sum * base + (str[i] - '0');
	return sum;
}

int main(){
	int num, base;
	char str[20];
	scanf("%d%d", &num, &base);
	for(int i = 0; i < num; i++){
		scanf("%s", str);
		printf("%d %d\n", base_to_10(str,base), base_to_10(reverse(str),base));
	}
	return 0;
}