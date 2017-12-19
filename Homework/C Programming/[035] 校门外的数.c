/*
 *	Name: [035] 校门外的数
 *	Author: Mega Chan
 *	Date: 2016.11.13 22:32
 */
 
 #include <stdio.h>

int main(){
	int len, num, head, last;
	scanf("%d%d", &len, &num);
	len++;
	int var[10000] = {0};
	for(int i = 0; i < num; i++){
		scanf("%d%d", &head, &last);
		for(int j = head; j <= last; j++){
			if(var[j] == 0){
				var[j] = -1;
				len--;
			}
		}
	}
	printf("%d\n", len);
	return 0;
}