/*
 *	Name: [2016 C Simulate Midterm] rectangle
 *	Author: Mega Chan
 *	Date: 2016.11.6 19:20
 */
 
 #include <stdio.h>

int main(){
	int num, var, flag, len[10][2][2];
	scanf("%d", &num);
	for(int i = 0; i < num; i++){
		flag = 0;
		scanf("%d", &var);
		for(int j = 0; j < var; j++){
			scanf("%d%d", &len[j][0][0], &len[j][0][1]);
			len[j][1][0] = len[j][0][1];
			len[j][1][1] = len[j][0][0];
		}
		for(int a = 0; a < var; a++){
			for(int b = 0; b < var; b++){
				for(int c = 0; c < var; c++){
					for(int x = 0; x < 2; x++){
						for(int y = 0; y < 2; y++){
							for(int z = 0; z < 2; z++){
								if(a == b || a == c || b == c)
									continue;
								if((len[a][x][0] == len[b][y][0] && len[a][x][0] == len[c][z][0])
									|| (len[a][x][0] + len[b][y][0] == len[c][z][0] && len[a][x][1] == len[b][y][1]))
									flag = 1;
							}
						}
					}
				}
			}
		}
		if(flag == 1)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}