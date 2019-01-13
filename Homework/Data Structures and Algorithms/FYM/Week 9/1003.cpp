// 1003. 排队接水
#include <iostream>
#include <iomanip>
#include <map>
using namespace std;

int main() {
  multimap<int, int> m;
  int n, var, sum = 0, add = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> var;
    m.insert(make_pair(var, i));
  }
  auto it = m.end();
  var = (--it)->second;
  m.erase(it);
  for (auto it = m.begin(); it != m.end(); it++) {
    cout << it->second << ' ';
    add += it->first;
    sum += add;
  }
  cout<< var << endl << fixed << setprecision(2) << sum / (double)n << endl;
}
