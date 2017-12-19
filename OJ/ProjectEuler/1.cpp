// Euler 001

#include <cstdio>

int sum(int n){
    return (1+n)*n/2;
}

int main(){
    int n, out;
    n = 1000;   //scanf("%d", &n);
    n--;
    out = sum(n/3)*3 + sum(n/5)*5 - sum(n/15)*15;
    printf("%d\n", out);
}
