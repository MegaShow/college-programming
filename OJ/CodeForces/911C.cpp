// C. Three Garlands
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  int k[3];
  cin >> k[0] >> k[1] >> k[2];
  sort(k, k + 3);
  if (k[0] == 1) cout << "YES" << endl;
  else if (k[0] == 2 && k[1] == 2) cout << "YES" << endl;
  else if (k[0] == 2 && k[1] == 4 && k[2] == 4) cout << "YES" << endl;
  else if (k[0] == 3 && k[2] == 3) cout << "YES" << endl;
  else cout << "NO" << endl;
}
