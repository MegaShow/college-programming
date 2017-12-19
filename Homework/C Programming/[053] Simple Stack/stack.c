/*
 *	Name: [053] Simple Stack
 *	Author: Mega Show
 *	Date: 2016.12.6
 */
 
#include <stdlib.h>
#include "stack.h"

int stack_push(int* stack, int num){
	if(stack[0] == STACK_MAX_SIZE)
		return 0;
	stack[0]++;
	stack[ stack[0] ] = num;
	return 1;
}

int stack_pop(int* stack){
	if(stack[0] == 0)
		return 0;
	stack[0]--;
	return 1;
}

int stack_top(int* stack, int* ret){
	if(stack[0] == 0)
		return 0;
	*ret = stack[ stack[0] ];
	return 1;
}

int *stack_constructor(void){
	int* stack = (int*)malloc(sizeof(int)*(STACK_MAX_SIZE+1));
	stack[0] = 0;
	return stack;
}

void stack_destructor(int* stack){
	free(stack);
}