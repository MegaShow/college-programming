/*
 *	Name: [064] Stack on link List
 *	Author: Mega Show
 *	Date: 2017.1.4
 */

#include <stdlib.h>
#include "stack.h"

void pop(Stack * stack){
    Node* n = stack->top;
    if(n != NULL){
        stack->top = stack->top->next;
        stack->size -= 1;
        free(n);
    }
}

int top(Stack * stack){
    return stack->top->data;
}

void push(Stack * stack, int data){
    Node* n = createNode(data, stack->top);
    stack->top = n;
    stack->size += 1;
}

int size(Stack * stack){
    return stack->size;
}

int empty(Stack * stack){
    return stack->size == 0;
}
