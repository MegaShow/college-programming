/*
ID: megaxiu1
LANG: C++
TASK: friday
*/

#include <cstdio>

int day[13] = {31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int var[7];

int main(){
    freopen("friday.in", "r", stdin);
    freopen("friday.out", "w", stdout);
    int year;
    int index = 2; // Monday
    scanf("%d", &year);
    year += 1900;
    for(int i = 1900; i < year; i++){
        for(int j = 1; j <= 12; j++){
            if( i == 1900 && j == 1)
                index = (index + 12) % 7;
            else if( j == 3 && ( (i % 4 == 0 && i % 100 != 0) || i % 400 == 0 ) )
                index = (index + 29) % 7;
            else
                index = (index + day[j-1]) % 7;
            var[index]++;
        }
    }
    for(int i = 0; i < 6; i++)
        printf("%d ", var[i]);
    printf("%d\n", var[6]);
}
