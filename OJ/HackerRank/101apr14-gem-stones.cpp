// MegaShow 2017.2.6

#include <cstdio>
#include <cstring>

int num[26];
bool flag[26];
int counter;

int main(){
    int n;
    char s[120];
    scanf("%d", &n);
    for(int j = 0; j < n; j++){
        memset(flag, 0, sizeof(flag));
        scanf("%s", s);
        for(int i = 0; s[i]; i++)
            flag[s[i]-'a'] = true;
        for(int i = 0; i < 26; i++)
            num[i] += flag[i];
        for(int i = 0; i < 26; i++){
            if(num[i] == n)
                counter++;
        }
    }
    printf("%d\n", counter);
}
