/* 4187 合法三角形 */

#include <cstdio>

int main(){
    int num, a, b, c;
    scanf("%d", &num);
    for(int i = 0; i < num; i++){
        scanf("%d%d%d", &a, &b, &c);
        if(a + b <= c || a + c <= b || b + c <= a)
            printf("NO\n");
        else
            printf("YES\n");
    }
    return 0;
}
