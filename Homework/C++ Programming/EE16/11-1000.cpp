/* Sicily 1147 谁拿了最多奖学金 */

#include <iostream>
#include <cstring>
using namespace std;

int main(){
	int num, grade, cgrade, paper, menoy, sum = 0, max = 0;
	char name[20], cadre, address, outName[20];
	cin >> num;
	for(int i = 0; i < num; i++){
		menoy = 0;
		cin >> name >> grade >> cgrade >> cadre >> address >> paper;
		if(grade > 80 && paper >= 1)
			menoy += 8000;
		if(grade > 85 && cgrade > 80)
			menoy += 4000;
		if(grade > 90)
			menoy += 2000;
		if(grade > 85 && address == 'Y')
			menoy += 1000;
		if(cgrade > 80 && cadre == 'Y')
			menoy += 850;
		if(menoy > max){
			max = menoy;
			strcpy(outName, name);
		}
		sum += menoy;
	}
	cout << outName << endl << max << endl << sum << endl;
	return 0;
}