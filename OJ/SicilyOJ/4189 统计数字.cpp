/* 4189 统计数字 */

#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int arr[200001];
int counter;

int main(){
    int num, var, a, b;
    scanf("%d", &num);
    while(num != 0){
        memset(arr, 0, sizeof(arr));
        for(int i = 0; i < num; i++)
            scanf("%d", &arr[i]);
        sort(arr, arr + num);
        var = arr[0];
        counter = 1;
        for(int i = 1; i < num; i++){
            if(arr[i] != var){
                counter++;
                var = arr[i];
            }
        }
        printf("%d\n", counter);
        scanf("%d", &num);
    }
    return 0;
}
