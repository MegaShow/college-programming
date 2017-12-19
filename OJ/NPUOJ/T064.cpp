/* T064.cpp 读取位图BMP，输出长宽 */

#include <iostream>
#include <fstream>
using namespace std;

void PrintBMPWH(char* path){
	ifstream fin;
	char temp[8];
	fin.open(path, ios::in | ios::binary);
	fin.seekg(18,ios::beg);
	cout << fin.get() + fin.get()*256 + fin.get()*256*256 + fin.get()*256*256*256 << ' ';
	cout << fin.get() + fin.get()*256 + fin.get()*256*256 + fin.get()*256*256*256 << endl;
	fin.close();
	return; 
}

int main(){
	char path[100] = "DATA5611.BMP";
	PrintBMPWH(path);
	return 0;
}