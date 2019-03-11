#include <iostream>
#include <vector>

using namespace std;

int main() {
    double t;
    int n, sum = 0;
    cin >> t >> n;
    vector<int> val(n), cut(n);
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    for (int i = 0; i <= 500; i++) {
        int min = 0, max = 0;
        for (int j = 0; j < n; j++) {
            min = val[j]/(cut[j]+1) < val[min]/(cut[min]+1) ? j : min;
            max = val[j]/(cut[j]+1) > val[max]/(cut[max]+1) ? j : max;
        }
        if (val[min]/(cut[min]+1) > val[max]/(cut[max]+1)*t) {
            break;
        }
        cut[max]++;
    }
    for (int i = 0; i < n; i++) {
        sum = sum + cut[i];
    }
    cout << sum << endl;
}

