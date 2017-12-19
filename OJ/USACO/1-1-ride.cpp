/*
ID: megaxiu1
LANG: C++
TASK: ride
*/
 
#include <fstream>
using namespace std;

int getvar(char str[]){
	if(str[0])
		return (str[0]-'A'+1) * getvar(str+1);
	return 1;
}

int main(){
	ofstream fout ("ride.out");
    ifstream fin ("ride.in");
	char comet[8], group[8];
	int var_comet = 1, var_group = 1;
	fin >> comet >> group;
	var_comet = getvar(comet);
	var_group = getvar(group);
	if(var_comet % 47 == var_group % 47)
		fout << "GO" << endl;
	else
		fout << "STAY" << endl;
	return 0;
}