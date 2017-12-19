// 1012. Sudoku rows
// MegaShow

//If in a 9x9 grid every row contains all numbers 1-9, it returns true, otherwise returns false.
bool rows(int r[9][9]){
    for(int i = 0; i < 9; i++){
        int arr[9];
        for(int j = 0; j < 9; j++)
            arr[j] = 0;
        for(int j = 0; j < 9; j++){
            if(r[i][j] <= 0 || r[i][j] > 9)
                return false;
            arr[r[i][j]-1]++;
        }
        for(int j = 0; j < 9; j++){
            if(arr[j] != 1)
                return false;
        }
    }
    return true;
}

/* test
#include <cstdio>
int main(){
    int r[9][9];
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++)
            r[i][j] = j+1;
    }
    printf("%d\n", (int)rows(r));
    r[3][5] = 1;
    printf("%d\n", (int)rows(r));
}*/