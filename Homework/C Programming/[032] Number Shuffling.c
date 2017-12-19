/*
 *	Name: [032] Number Shuffling
 *	Author: Mega Chan
 *	Date: 2016.11.19 19:33
 */
 
#include <stdio.h>
#include <stdlib.h>

void print_random(int* var, int num){
	int top, temp;
	for(int i = num - 1; i > 0; i--){
		top = rand() % (i + 1);
		temp = var[top];
		var[top] = var[i];
		var[i] =temp;
	}
	printf("{");
	for(int i = 0; i < num - 1; i++)
		printf("%d, ", var[i]);
	printf("%d}\n", var[num-1]);
}

void int_arr_assign(int* var, int* out, int num){
	for(int i = 0; i < num; i++)
		out[i] = var[i];
}

int main(){
	int num, seed, var[100], out[100];
	scanf("%d", &num);
	for(int i = 0; i < num; i++)
		scanf("%d", &var[i]);
	scanf("%d", &seed);
	srand(seed);
	for(int i = 0; i < 2; i++){
		int_arr_assign(var, out, num);
		print_random(out, num);
	}
	return 0;
}