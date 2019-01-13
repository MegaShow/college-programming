/* 1000 Grading a multiple-choice exam */

#include <iostream>
#include <cstring>
using namespace std;

int main(){
	int id;
	char arr[50], std[21];
	cin >> std >> id;
	while(id){
		cout << id << " ";
		cin >> arr;
		if(strlen(arr) > 20)
			cout << "Too many answers" << endl;
		else if(strlen(arr) < 20)
			cout << "Too few answers" << endl;
		else{
			int right = 0;
			bool flag = 1;
			for(int i = 0; i < 20; i++){
				if(arr[i] < 'a' || arr[i] > 'f'){
					flag = 0;
					break;
				}
				if(arr[i] == std[i])
					right++;
			}
			if(flag)
				cout << right << endl;
			else
				cout << "Invalid answers" << endl;
		}
		cin >> id;
	}
	return 0;
}