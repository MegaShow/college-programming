// 1000. Minimum Weight
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct HuffmanTree {
  int weight;
  HuffmanTree* left;
  HuffmanTree* right;
  HuffmanTree(int _weight, HuffmanTree* _left = nullptr, HuffmanTree* _right = nullptr)
    :weight(_weight), left(_left), right(_right) {}
};

int getTreeWeight(HuffmanTree* node, int height);

int main() {
  int case_num;
  cin >> case_num;
  while (case_num--) {
    int weight;
    vector<HuffmanTree*> v_weight;
    cin >> weight;
    while (weight) {
      v_weight.push_back(new HuffmanTree(weight));
      cin >> weight;
    }
    sort(v_weight.begin(), v_weight.end(), [](HuffmanTree* a, HuffmanTree* b) -> bool {
      return a->weight < b->weight;
    });
    for (int i = 0; i < v_weight.size() - 1; i++) {
      HuffmanTree* parent = new HuffmanTree(v_weight[i]->weight + v_weight[i+1]->weight,
        v_weight[i], v_weight[i+1]);
      int index = i + 1;
      while (index + 1 < v_weight.size() && v_weight[index + 1]->weight < parent->weight) {
        v_weight[index] = v_weight[index + 1];
        index++;
      }
      v_weight[index] = parent;
    }
    cout << getTreeWeight(v_weight[v_weight.size() - 1], 0) << endl;
  }
}

int getTreeWeight(HuffmanTree* node, int height) {
  if (node->left == nullptr && node->right == nullptr) return height * node->weight;
  return getTreeWeight(node->left, height + 1) + getTreeWeight(node->right, height + 1);
}
