#define METHOD 1

/* C001.cpp 输入字符串和一个字符c，删掉字符串里面的c，并输出最终的字符串 */

/* method 1 */
#if METHOD == 1

#include <iostream>
using namespace std;

int main(){
	char c, str[1000], out[1000];
	cin.getline(str,999);
	cin >> c;
	int i = 0, j = 0;
	while(str[i] != 0){
		if(str[i] != c)
			out[j++] = str[i];
		i++;
	}
	cout << out << endl;
	return 0; 
}


/* method 2 */
#elif METHOD == 2

#include <iostream>
#include <cstring>
using namespace std;

int main(){
	char c, str[1000];
	cin.getline(str, 999);
	cin >> c;
	int len = strlen(str);
	for(int i = 0; i < len; ){
		if(str[i] == c){
			len--;
			for(int j = i; j < len; j++)
				str[j] = str[j+1];
		}
		else
			i++;
	}
	for(int i = 0; i < len; i++)
		cout << str[i];
	cout << endl;
	return 0;
}

#endif