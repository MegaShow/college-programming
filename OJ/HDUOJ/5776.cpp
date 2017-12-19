// HDU5776 MegaShow 2017.2.6

#include <cstdio>

int main(){
    int t, n, m;
    scanf("%d", &t);
    while(t--){
        scanf("%d%d", &n, &m);
        int arr[n], sum = 0, p[m] = {0}, flag = 0;
        p[0] = 1;
        for(int i = 0; i < n; i++){
            scanf("%d", &arr[i]);
            sum += arr[i];
            if(p[sum % m] == 1)
                flag = 1;
            p[sum % m] = 1;
        }
        if(flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
