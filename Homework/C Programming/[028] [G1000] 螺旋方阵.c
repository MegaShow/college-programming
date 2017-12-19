/*
 *	Name: [028][G 1000] 螺旋方阵
 *	Author: Mega Chan
 *	Date: 2016.11.6 7:55
 */

#include <stdio.h>

int main(){
	int var, angle = 0;
	scanf("%d", &var);
	int num[100][100] = {0};
	int var2 = var * var;
	for(int i = 1, x = 0, y = 0; i <= var2; i++){
		num[x][y] = i;
		switch(angle % 4){
			case 0: if(x == var - 1 || num[x+1][y] != 0) angle++; break;
			case 1: if(y == var - 1 || num[x][y+1] != 0) angle++; break;
			case 2: if(x == 0 || num[x-1][y] != 0) angle++; break;
			case 3: if(y == 0 || num[x][y-1] != 0) angle++; break;
		}
		switch(angle % 4){
			case 0: x++; break;
			case 1: y++; break;
			case 2: x--; break;
			case 3: y--; break;
		}
	}
	for(int y = 0; y < var; y++){
		for(int x = 0; x < var - 1; x++)
			printf("%d ", num[x][y]);
		printf("%d\n", num[var-1][y]);
	}
	return 0;
}