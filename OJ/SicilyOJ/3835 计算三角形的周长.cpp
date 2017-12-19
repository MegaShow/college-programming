/* 3835 计算三角形的周长 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double MySqrt(double a, double b, double c, double d){
	return sqrt((a-c)*(a-c)+(b-d)*(b-d));
}

int main(){
	int num;
	double x1, x2, x3, y1, y2, y3;
	cin >> num;
	for(int i = 0; i < num; i++){
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
		cout << setiosflags(ios::fixed) << setprecision(5)
		     << MySqrt(x1,y1,x2,y2) + MySqrt(x1,y1,x3,y3) + MySqrt(x2,y2,x3,y3) << endl;
	}
	return 0;
}