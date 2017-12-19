/* 1348 2^k进制数 */

#include <cstdio>
#include <cstring>

#define MAX 100000000
#define print() printf("%08d", a[i])

int C[513][514][26];

void Add_BCtoA(int a[], int b[], int c[]){
	int next = 0;
	a[0] = (b[0] >= c[0] ? b[0] : c[0]);
	for(int i = 1; i <= a[0]; i++){
		a[i] = b[i] + c[i] + next;
		next = a[i] / MAX;
		a[i] %= MAX;
	}
	if(next){
		a[0]++;
		a[a[0]] = next;
	}
}

void Add_BtoA(int a[], int b[]){
	int next = 0;
	a[0] = (a[0] >= b[0] ? a[0] : b[0]);
	for(int i = 1; i <= a[0]; i++){
		a[i] = a[i] + b[i] + next;
		next = a[i] / MAX;
		a[i] %= MAX;
	}
	if(next){
		a[0]++;
		a[a[0]] = next;
	}
}

void PrintArr(int a[]){
	if(a[0] == 0){
		printf("0\n");
		return;
	}
	printf("%d", a[a[0]]);
	for(int i = a[0] - 1; i > 0; i--)
		print();
	printf("\n");
}

void GetC(int n){
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= i; j++){
			if(j == 0)
				C[j][i][0] = C[j][i][1] = 1;
			else
				Add_BCtoA(C[j][i], C[j-1][i-1], C[j][i-1]);
		}
	}
}

int main(){
	int k, w;
	//scanf("%d%d", &k, &w);
	while(~scanf("%d%d", &k, &w)){
		int sum[26];
		memset(C, 0, sizeof(C));
		memset(sum, 0, sizeof(sum));
		int base = (1 << k) - 1;
		int high =  w % k;
		int high_base = (1 << high) - 1;
		int num = w / k;   // 大数具有完整2^k的位数
		GetC(base);
		for(int i = 2; i <= num && i <= base; i++)
			Add_BtoA(sum, C[i][base]);
		for(int i = 1; i <= high_base && num <= base - i; i++)
			Add_BtoA(sum, C[num][base-i]);
		PrintArr(sum);
	}
}
