// 1012. Find the mean
#include <map>
using namespace std;

double mean(map<int, double> p) {
  double x_ = 0;
  for (auto &i: p) {
    x_ += (i.first * i.second);
  }
  return x_;
}

int main() {}
