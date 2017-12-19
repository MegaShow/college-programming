/*
 *	Name: [027][H 1003] 小壕的礼物
 *	Author: Mega Chan
 *	Date: 2016/10/31 14:31
 */

#include <stdio.h>

int main(){
	int num, order, var_top = 0;
	char var[100][50];
	scanf("%d",&num);
	for(int i = 0;i < num;i++){
		scanf("%d%s",&order,var[var_top]);
		if(order == 1)
			var_top++;
		else{
			printf("%s %s\n",var[var_top],var[var_top-1]);
			var_top--;
		}
	}
	return 0;
}