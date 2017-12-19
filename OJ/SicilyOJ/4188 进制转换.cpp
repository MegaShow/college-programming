/* 4188 进制转换 */

#include <cstdio>

int main(){
    int num, var;
    scanf("%d", &num);
    for(int i = 0; i < num; i++){
        scanf("%d", &var);
        bool flag = false;
        if(var == 0)
            printf("0\n");
        else{
            for(int k = 31; k >= 0; k--){
                if(flag)
                    printf("%d", (var >> k) & 1);
                else{
                    if((var >> k) & 1){
                        flag = true;
                        printf("1");
                    }
                }
            }
            printf("\n");
        }
    }
    return 0;
}
