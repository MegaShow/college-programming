/* C003.cpp 实现换行结束输入数组 */

/* METHOD-1 scanf */

/*#include <iostream>
#include <cstdio>
using namespace std;

int arr[10000];
char c;

int main(){
    int index;
    for(index = 0; c != '\n' ; index++)
        scanf("%d%c", &arr[index], &c);
        //cin >> arr[index] >> c;
    for(int i = 0; i < index - 1; i++)
        cout << arr[i] << ' ';
    cout << arr[index-1] << endl;
}*/

/* METHOD-2 getchar */

#include <iostream>
using namespace std;

int arr[10000];
char c;
int index;

int main(){
    while(c != '\n'){
        while((c = getchar()) != ' ' && c != '\n')
            arr[index] = arr[index] * 10 + c - '0';
        index++;
    }
    for(int i = 0; i < index - 1; i++)
        cout << arr[i] << ' ';
    cout << arr[index-1] << endl;
}
