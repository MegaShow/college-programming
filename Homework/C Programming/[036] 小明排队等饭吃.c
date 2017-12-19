/*
 *	Name: [036] 小明排队等饭吃
 *	Author: Mega Chan
 *	Date: 2016.11.19 12:03
 */
 
#include <stdio.h>

int main(){
	int first_num, n, var, time, sum = 0;
	scanf("%d", &first_num);
	for(int i = 0; i < first_num; i++){
		scanf("%d", &time);
		sum += time;
	}
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d%d", &var, &time);
		if(var < first_num){
			first_num++;
			sum += time;
		}
	}
	printf("%d\n", sum);
	return 0;
}