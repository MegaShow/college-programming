// 1077. 快速排序的划分
#include <vector>
using namespace std;

int Partition(vector<int>& R, int low, int high) {
  // 对记录子序列R[low..high]进行一趟快速排序，并返回枢轴记录所在位置，
  // 使得在它之前的记录的关键字均不大于它的关键字，在它之后的记录的关键
  // 字均不小于它的关键字
  R[0] = R[low];
  int pivotkey = R[low];    // 枢轴记录关键字
  while (low < high) {        // 从表的两端交替地向中间扫描
    while(low < high && R[high] >= pivotkey)
      high--;
    if (low < high)
      R[low++] = R[high];  // 将比枢轴记录小的记录移到低端
    while (low < high && R[low] <= pivotkey)
      low++;
    if (low < high)
      R[high--] = R[low];  // 将比枢轴记录大的记录移到高端
  } //while
  R[low] = R[0];            // 枢轴记录移到正确位置
  return low;               // 返回枢轴位置
} // Partition

int main() {}
