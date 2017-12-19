/**
  @intro: Main
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const double global_e = 0.00000001;  // 迭代精度
const double global_out_fix = 4;  // 输出的位数

/**
  @intro: 计算网页重要性的迭代函数, PageRank矩阵计算

  @param: vector<double>& v          - 网页访问概率
  @param: vector<vector<double> >& m - 网页指向关系 m[i][j] 表示i指向j的次数
*/
bool pageRank(vector<double>& v, vector<vector<double> >& m, double e) {
  vector<double> vnew = v;
  int size = v.size();
  for (int i = 0; i < size; i++) {
    double sum = 0;
    for (int j = 0; j < size; j++) {
      sum = sum + v[j] * m[j][i];
    }
    vnew[i] = sum;
  }
  bool flag = false;
  for (int i = 0; i < v.size(); i++) {
    if (abs(v[i] - vnew[i]) > e) {
      flag = true;
      break;
    }
  }
  if (flag) {
    v = vnew;
  }
  return flag;
}


/**
  @intro: 扫描输入网页指向关系的数据, 并处理得到关系权重

  @param: vector<vector<double> >& m - 网页指向关系 m[i][j] 表示i指向j的次数, 用于储存
  @param: int size                   - 网页个数
*/
void scan(vector<vector<double> >& m, int size) {
  for (int i = 0; i < size; i++) {
    double sum = 0;
    vector<double> v;
    for (int j = 0; j < size; j++) {
      double val;
      cin >> val;
      if (i == j) val = 0;
      sum += val;
      v.push_back(val);
    }
    m.push_back(v);
  }
}


/**
  @intro: 输出网页访问概率

  @param: vector<double>& v - 网页访问概率
*/
void print(vector<double>& v) {
  cout << "The answer:" << endl;
  if (v.size()) {
    cout << fixed << setprecision(global_out_fix) << v[0];
    for (int i = 1; i < v.size(); i++) {
      cout << ' ' << v[i];
    }
    cout << endl << endl;
  }
}


/**
  @intro: 网页访问概率排序

  @param: vector<double>& v - 网页访问概率
*/
void pageSort(vector<double>& v) {
  vector<pair<pair<double, int>, int> > p;
  for (int i = 0; i < v.size(); i++) {
    p.push_back(make_pair(make_pair(v[i], i), 0));
  }
  sort(p.begin(), p.end(), [](pair<pair<double, int>, int> a, pair<pair<double, int>, int> b) {
    return a.first.first > b.first.first;
  });
  for (int i = 0; i < p.size(); i++) {
    p[i].second = i + 1;
  }
  sort(p.begin(), p.end(), [](pair<pair<double, int>, int> a, pair<pair<double, int>, int> b) {
    return a.first.second <= b.first.second;
  });
  if (p.size()) {
    cout << p[0].second;
    for (int i = 1; i < p.size(); i++) {
      cout << ' ' << p[i].second;
    }
    cout << endl;
  }
}


/**
  @intro: 处理网页指向关系的原始矩阵数据, 使之不存在0

  @param: vector<vector<double> >& m - 原始矩阵数据

  @output: m - 输入的网页指向关系矩阵
  @output: W - 通过 Wij = 2 - 1 / (2 ^ m[i][j]) 所得的矩阵
  @output: R - 通过 Rij = 1 / ((Wi.Sum + 1) * size)  所得的矩阵, 与j无关
  @output: P - 通过 Pij = Wij / (Wi.Sum + 1) + Rij 所得的矩阵, 为网页指向关系的最终权重
*/
int createMatrix(vector<vector<double> >& m) {
  int size = m.size();
  vector<double> v;
  for (int i = 0; i < size; i++) {
    v.push_back(static_cast<double>(1) / size);
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout << m[i][j] << '\t';
    }
    cout << endl;
  }
  vector<vector<double> > w;
  cout << fixed << setprecision(global_out_fix);
  cout << endl << "Wij:" << endl;
  for (int i = 0; i < size; i++) {
    vector<double> v;
    for (int j = 0; j < size; j++) {
      double tmp;
      if (m[i][j] > 20) {
        tmp = 2 - ((double)1 / pow(2, 20));
      } else{
        tmp = 2 - ((double)1 / pow(2, m[i][j] - 1));
      }
      cout << tmp << '\t';
      v.push_back(tmp);
    }
    w.push_back(v);
    cout << endl;
  }
  cout << endl << "Rij:" << endl;
  vector<vector<double> > r;
  vector<double> vSum;
  for (int i = 0; i < size; i++) {
    vector<double> v;
    double sum = 0;
    for (int j = 0; j < size; j++) {
      sum += w[i][j];
    }
    vSum.push_back(sum);
    double numR = (double)1 / (sum + 1) * ((double)1 / size);
    for (int j = 0; j < size; j++) {
      cout << numR << '\t';
      v.push_back(numR);
    }
    r.push_back(v);
    cout << endl;
  }
  vector<vector<double> > p;
  cout << endl << "Pij:" << endl;
  for (int i = 0; i < size; i++) {
    vector<double> v;
    for (int j = 0; j < size; j++) {
      double tmp = w[i][j] / (vSum[i] + 1) + r[i][j];
      cout << tmp << '\t';
      v.push_back(tmp);
    }
    p.push_back(v);
    cout << endl;
  }
  m = p;
}


/**
  @intro: 主函数

  @input: int size         - 网页个数
  @input: int m[size][size] - 网页指向关系, 前者指向后者

  @output: 通过changeWeight之后的矩阵
  @output: 每一次执行迭代后的网页访问概率
*/
int main() {
  int size;
  vector<vector<double> > m;
  vector<double> v;
  cin >> size;
  scan(m, size);
  createMatrix(m);
  for (int i = 0; i < size; i++) {
    v.push_back(static_cast<double>(1) / size);
  }
  cout << endl;
  print(v);
  int counter = 0;
  while (pageRank(v, m, global_e)) {
    counter++;
  }
  cout << "Counter: " << counter << endl << endl;
  print(v);
  pageSort(v);
}
