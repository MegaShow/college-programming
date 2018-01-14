// 1150. 简单魔板[Special judge]
#include <iostream>
using namespace std;

int arr[8];
char step_opr[11];
int step_out;

void DFS(int step, int limit_step);
void StepA();
void StepB();
void StepC();
void ReStepA();
void ReStepB();
void ReStepC();

void Print() {
  for (int i = 0; i < 4; i++) {
    cout << arr[i] << ' ';
  }
  cout << endl;
  for (int i = 7; i >= 4; i--) {
    cout << arr[i] << ' ';
  }
  cout << endl;
}

int main() {
  int limit_step;
  cin >> limit_step;
  while (limit_step != -1) {
    for (int i = 0; i < 4; i++) {
      cin >> arr[i];
    }
    for (int i = 7; i >= 4; i--) {
      cin >> arr[i];
    }
    step_out = -1;
    DFS(0, limit_step);
    if (step_out == -1) step_out = 0;
    step_opr[step_out] = 0;
    cout << step_out << ' ' << step_opr << endl;
    cin >> limit_step;
  }
}

void DFS(int step, int limit_step) {
  if (step == limit_step + 1 || step_out != -1) return;
  bool flag = true;
  for (int i = 0; i < 8; i++) {
    if (arr[i] != i + 1) flag = false;
  }
  if (flag) {
    step_out = step;
    return;
  }
  if (step_out == -1) {
    ReStepA();
    step_opr[step] = 'A';
    DFS(step + 1, limit_step);
    StepA();
  }
  if (step_out == -1) {
    ReStepB();
    step_opr[step] = 'B';
    DFS(step + 1, limit_step);
    StepB();
  }
  if (step_out == -1) {
    ReStepC();
    step_opr[step] = 'C';
    DFS(step + 1, limit_step);
    StepC();
  }
}

void StepA() {
  int val;
  for (int i = 0; i < 4; i++) {
    val = arr[i];
    arr[i] = arr[7-i];
    arr[7-i] = val;
  }
}

void ReStepA() {
  StepA();
}

void StepB() {
  int val1 = arr[3], val2 = arr[4];
  for (int i = 2; i >= 0; i--) {
    arr[i + 1] = arr[i];
    arr[6 - i] = arr[7 - i];
  }
  arr[0] = val1;
  arr[7] = val2;
}

void ReStepB() {
  int val1 = arr[0], val2 = arr[7];
  for (int i = 0; i <= 2; i++) {
    arr[i] = arr[i + 1];
    arr[7 - i] = arr[6 - i];
  }
  arr[3] = val1;
  arr[4] = val2;
}

void StepC() {
  int val = arr[1];
  arr[1] = arr[6];
  arr[6] = arr[5];
  arr[5] = arr[2];
  arr[2] = val;
}

void ReStepC() {
  int val = arr[1];
  arr[1] = arr[2];
  arr[2] = arr[5];
  arr[5] = arr[6];
  arr[6] = val;
}
