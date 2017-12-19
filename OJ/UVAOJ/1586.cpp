// UVA1586 MegaShow 2017.2.3

#include <cstdio>
#include <cstdlib>
#include <cstring>

double arr[26];

int main(){
    arr['C'-'A'] = 12.01;
    arr['H'-'A'] = 1.008;
    arr['O'-'A'] = 16.00;
    arr['N'-'A'] = 14.01;
    int n, len;
    char str[100];
    double sum;
    scanf("%d", &n);
    while(n--){
        scanf("%s", str);
        sum = 0;
        len = strlen(str);
        int i = 0;
        while(i < len){
            if(str[i+1] >= '0' && str[i+1] <= '9'){
                sum += arr[str[i]-'A'] * atoi(&str[i+1]);
                while(str[i+1] >= '0' && str[i+1] <= '9')
                    i++;
            }
            else
                sum += arr[str[i]-'A'];
            i++;
        }
        printf("%.3lf\n", sum);
    }
}
