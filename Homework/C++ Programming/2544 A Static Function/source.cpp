#include<iostream>
#include"source.h"
using namespace std;
Exp* a[110];
int main() {
    //freopen("in","r",stdin);
    //freopen("out","w",stdout);
    int T;
    cin >> T;
    while (T--) {
        cout << "Initial exp : " <<Exp::get_Exp() << endl;
        int n;
        cin >> n;
        int tot = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            if (x == 1) {
                a[++tot] = new Exp();
            } else {
                if (tot >= 0) {
                    if (a[tot]) delete a[tot];
                    a[tot] = NULL;
                    tot--;
                }
            }
            cout << "Current exp : " << Exp::get_Exp() << endl;
        }
    }
}
