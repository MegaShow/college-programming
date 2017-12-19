/* 3836 计算组合数 */

#include <iostream>
using namespace std;

int c(int n, int m){
	if(m == 1)
		return n;
	else if(m == n || m == 0)
		return 1;
	return c(n-1, m) + c(n-1, m-1);
}

int main(){
	int var, n, m; /* n >= m */
	cin >> n >> m;
	while(n != 0 || m != 0){
		cout << c(n, m) << endl;
		cin >> n >> m;
	}
}