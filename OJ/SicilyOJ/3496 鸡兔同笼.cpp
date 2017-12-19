/* 3496 鸡兔同笼 */

#include <iostream>
using namespace std;

int main(){
	int chicken, rabbit, head, foot;
	cin >> head >> foot;
	while(head != 0 || foot != 0){
		if((foot - 2 * head) % 2 != 0 || foot < 2 * head || 4 * head < foot)
			cout << "No answer" << endl;
		else{
			rabbit = (foot - 2 * head) / 2;
			chicken = (4 * head - foot) / 2;
			cout << chicken << " " << rabbit << endl;
		}
		cin >> head >> foot;
	}
	return 0;
}