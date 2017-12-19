#include <string>
#include <cstring>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
	string a,b;
//	cin >> a ;
//	reverse(a.begin(), a.end());
//	cout << a;
	while(1)
	{
		cin >> a >> b;
		int ai, bi;
		for (int i=0; i<a.size(); i++)
		{
			if(a[i] != '0')
			{
				ai = i;
				break;
			}
		}
		for (int i=0; i<b.size(); i++)
		{
			if(b[i]!='0')
			{
				bi = i;
				break;
			}
		}

		if ((a.size()-ai) > (b.size() - bi)) {
			printf(">\n");
		}
		else if ((a.size()-ai) < (b.size() - bi)) {
			printf("<\n");
		}
		else {
			bool flag = false;
			while ((ai<a.size()) && (bi<b.size())) {
				if (a[ai] > b[bi]) {
					flag = true ;
					printf(">\n");
					break;
				}
				else if (a[ai] < b[bi]) {
					flag = true ;
					printf("<\n");
					break;
				}
				ai++;
				bi++;
			}
			if (flag == false) printf("=\n");
		}
	}
}
