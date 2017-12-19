// 1005. 判断关系的对称性（给出关系的描述）
// MegaShow

#include <cstdio>

int main(){
    int n, m, a, b;
    scanf("%d", &n);
    int* set = new int[n];
    bool** matrix = new bool*[n];
    for(int i = 0; i < n; i++)
        matrix[i] = new bool[n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            matrix[i][j] = false;
    }

    for(int i = 0; i < n; i++)
        scanf("%d", &set[i]);
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        scanf("%d%d", &a, &b);
        for(int k = 0; k < n; k++){
            if(set[k] == a){
                a = k;
                break;
            }
        }
        for(int k = 0; k < n; k++){
            if(set[k] == b){
                b = k;
                break;
            }
        }
        matrix[a][b] = true;
    }
    bool flag = true;
    for(int i = 0; i < n; i++){
        for(int k = i; k < n; k++){
            if(matrix[i][k] != matrix[k][i]){
                flag = false;
            }
        }
    }
    printf("%d\n", (int)flag);

    delete [] set;
    for(int i = 0; i < n; i++)
        delete [] matrix[i];
    delete [] matrix;
    return 0;
}
