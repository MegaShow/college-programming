/* 3712 Matrix Multiplication */

#include <iostream>
using namespace std;

int main(){
	int n;
	long long sum;
	while(cin >> n){
		int a[n][n], b[n][n];
		for(int y = 0; y < n; y++)
			for(int x = 0; x < n; x++)
				cin >> a[y][x];
		for(int y = 0; y < n; y++)
			for(int x = 0; x < n; x++)
				cin >> b[y][x];
		for(int y = 0; y < n; y++){
			for(int x= 0; x < n; x++){
				sum = 0;
				for(int axby = 0; axby < n; axby++)
					sum += a[y][axby] * b[axby][x];
				if(x != n - 1)
					cout << sum << " ";
				else
					cout << sum << endl;
			}
		}
	}
	return 0;
}