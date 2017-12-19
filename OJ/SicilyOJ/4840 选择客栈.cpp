/* 4840 选择客栈 */
/* NOIP 2011 */

/* 本题因为Time Limit的问题，使用了将所有配对减去不符合的配对的方式 
 * 因为不符合的配对price在数组中是连续的false(bool)
 * 所以连续的处理可以将复杂度降至O(n) 
 */

#include <iostream>
#include <cstring>
using namespace std;

int main(){
	int n, k, p, sum = 0, temp_price, no_sum = 0;
	cin >> n >> k >> p;
	int color[n+1], num[k];
	bool price[n+1];
	for(int i = 1; i <= n; i++){
		cin >> color[i] >> temp_price;
		if(temp_price <= p)
			price[i] = 1;
		else
			price[i] = 0;
	}
	
	memset(num, 0, sizeof(num));
	for(int i = 1; i <= n; i++){
		if(price[i] == 0){
			no_sum += num[ color[i] ];
			num[ color[i] ] ++;
		}
		else
			memset(num, 0, sizeof(num));
	}
	
	memset(num, 0, sizeof(num));
	for(int i = 1; i <=n; i++){
		sum += num[ color[i] ];
		num[ color[i] ]++;
	}
	cout << sum - no_sum << endl;
	return 0;
}