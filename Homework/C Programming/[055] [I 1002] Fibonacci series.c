/*
 *	Name: [055] [I 1002] Fibonacci series
 *	Author: Mega Show
 *	Date: 2016.12.6
 */
 
#include <stdio.h>

int arr[48] = {0, 1};
int index = 1;

int main(){
	int num, var;
	scanf("%d", &num);
	for(int i = 0; i < num; i++){
		scanf("%d", &var);
		if(var > arr[index]){
			while(var > arr[index]){
				index++;
				arr[index] = arr[index - 1] + arr[index - 2];
			}
		}
		if(var <= arr[index]){
			for(int k = index; k >= 0; k--){
				if(var == arr[k]){
					printf("%d\n", k + 1);
					break;
				}
				else if(var > arr[k]){
					printf("0\n");
					break;
				}
			}
		}
	}
}