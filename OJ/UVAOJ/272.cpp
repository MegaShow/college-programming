// UVA272 MegaShow 2017.1.25

#include <cstdio>

int main(){
    char c;
    bool flag = false;
    while(~scanf("%c", &c)){
        if(c == '\"' && flag == false){
            printf("``");
            flag = true;
        }
        else if(c == '\"' && flag){
            printf("\'\'");
            flag = false;
        }
        else
            printf("%c", c);
    }
    return 0;
}
