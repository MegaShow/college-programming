/* Time Limit Exceeded */

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

char arr[102][10002];

int main(){
    int n, m, p;
    int operate;
    int type;
    int x, y;
    int x1, x2;
    char temp;
    /*for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            arr[i][j] = '.';
        }
    }*/
    vector<char*> a, b;
    memset(arr, '.', sizeof(arr));
    scanf("%d%d%d", &n, &m, &p);
    for(int i = 0; i < p; i++){
        scanf("%d", &operate);
        if(operate == 1){
            scanf("%d%d%d", &type, &x, &y);
            if(type == 1)
                arr[x][y] = 'w';
            else
                arr[x][y] = 'b';
        }
        else{
            scanf("%d%d", &x1, &x2);
            //char* temp;
            //temp = *arr + x2 - 1;
            //arr[x1-1] = arr[x2-1];
            //arr[x2-1] = temp;
            //a.push_back(arr[x1]);
            //b.push_back(arr[x2]);
            //swap(a, b);
            for(int j = 0; j < m; j++){
                temp = arr[x1-1][j];
                arr[x1-1][j] = arr[x2-1][j];
                arr[x2-1][j] = temp;
            }
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}
