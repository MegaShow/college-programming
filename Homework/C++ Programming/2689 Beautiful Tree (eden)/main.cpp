#include <iostream>
#include <cstring>
#include <string>
#include "BeautifulTree.hpp"
using namespace std;
using namespace HFM;

 void test_HFM() {
    cout << "---------- test_HFM ----------\n# TEST_1\n";
    int weight[] = { 7, 4, 5, 2 };
    int count = 4;
    HuffmanCode HFC(weight, count);
    HFC.DisplayCode();
    cout << "\nTEST_2\n";
    string input = "you are the apple in my eyes";
    HuffmanCode HFC_2(input);
    HFC_2.DisplayCode();
}
 void hard_test() {
    cout << "---------- test_HFM ----------\n# TEST_1\n";
    int count, weight_arr[20] = {0};
    cin >> count;
    for (int i = 0; i < count; i++) cin >> weight_arr[i];
    HuffmanCode HFC(weight_arr, count);
    HFC.DisplayCode();
    cout << "\nTEST_2\n";
    string input = "";
    cin >> input;
    HuffmanCode HFC_2(input);
    HFC_2.DisplayCode();
}
 int main() {
    int t;
    cin >> t;
    if (t == 0) {
        test_HFM();
    } else {
        hard_test();
    }
    return 0;
}
/*
 namespace HFM {
 class HuffmanCode {
   public:
    explicit
    HuffmanCode(const string &str)
    HuffmanCode(int w[], int n)
    void DisplayCode()
 };
}  // namespace HFM
*/
 