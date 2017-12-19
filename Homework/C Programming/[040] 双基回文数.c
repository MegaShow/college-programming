/*
 *	Name: [040] 双基回文数
 *	Author: Mega Chan
 *	Date: 2016.11.14 20:45
 */
 
#include <stdio.h>

/* global variable, arr[0] store the lowest digit */
int arr[1000];

/* to judge if a number is palindrome number or not */
int palindrome(int top){
	if(arr[0] == 0)
		return 0;
	for(int i = 0; i <= top / 2; i++)
		if(arr[i] != arr[top-i])
			return 0;
	return 1;
}

/* set array of number, and return the array 's top */
int setstr(int var, int base){
	int top = -1;
	while(var){
		top++;
		arr[top] = var % base;
		var /= base;
	}
	return top;
}

/* main function */
int main(){
	int num, var, counter;
	scanf("%d", &num);
	for(int i = 0; i < num; i++){
		scanf("%d", &var);
		while(var++){
			counter = 0;
			for(int j = 2; j <= 10; j++)
				if( palindrome(setstr(var, j)) )
					counter++;
			if(counter >= 2)
				break;
		}
		printf("%d\n", var);
	}
	return 0;
}