/*
 *	Name: [038] Simple Queue
 *	Author: Mega Chan
 *	Date: 2016.11.14 16:45
 */
 
#include <stdio.h>

int main(){
	int operator, var, top = -1, queue[20];
	while(scanf("%d", &operator) != EOF){
		if(operator){	// 1, push_back
			if(top == 9){
				printf("Push Failed. The queue is full.\n");
				scanf("%d", &var);
			}
			else{
				top++;
				for(int i = top; i > 0; i--)
					queue[i] = queue[i-1];
				scanf("%d", &var);
				queue[0] = var;
			}
		}
		else{	// 2, pop_back
			if(top == -1)
				printf("Pop Failed. The queue is empty.\n");
			else{
				printf("%d\n", queue[top]);
				top--;
			}
		}
	}
	return 0;
}