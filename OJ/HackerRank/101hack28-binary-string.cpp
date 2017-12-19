// binary string

#include <cstdio>
#include <queue>
using namespace std;

int main(){
    int n, k, t;
    scanf("%d%d%d", &n, &k, &t);
    char s[n+2];
    scanf("%s", s);
    queue <int> p[k];
    for(int i = 0; i < n; i++){
        if(s[i] == '1')
            p[i%k].push(i);
    }
    for(int i = 0; i < n; i++){
        if(s[i] == '0' && !p[i%k].empty() && (p[i%k].front() - i) / k <= t){
            t -= (p[i%k].front() - i) / k;
            s[i] = '1';
            s[p[i%k].front()] = '0';
            p[i%k].pop();
        }
        else if(s[i] == '1')
            p[i%k].pop();
    }
    printf("%s\n", s);
}
