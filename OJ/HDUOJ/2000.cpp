// HDU2000 MegaShow 2017.1.26

#include <cstdio>

void swap_c(char *a, char *b){
    if(*a > *b){ int d = *b; *b = *a; *a = d; }
}

int main(){
    char a, b, c, d;
    while(~(a = getchar())){
        b = getchar();
        c = getchar();
        swap_c(&b, &c);
        swap_c(&a, &b);
        swap_c(&b, &c);
        printf("%c %c %c\n", a, b, c);
        getchar();
    }
}
