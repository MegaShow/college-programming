// A. Nearest Minimums
#include <iostream>
#include <map>
using namespace std;

int main() {
  int number, val;
  cin >> number;
  map<int, int> distance;
  map<int, int> position;
  int min;
  if (number) {
    cin >> min;
    position.insert(make_pair(min, 0));
  }
  for (int i = 1; i < number; i++) {
    cin >> val;
    if (val < min) min = val;
    if (position.count(val)) {
      if (!distance.count(val) || distance[val] > i - position[val]) {
        distance[val] = i - position[val];
      }
    }
    position[val] = i;
  }
  cout << distance[min] << endl;
}
