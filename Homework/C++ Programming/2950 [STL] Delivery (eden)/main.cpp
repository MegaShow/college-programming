#include <iostream>
#include <vector>
#include <string>
#include "Delivery.hpp"
 using std::string;
 int main() {
    std::vector<string> info;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string temp;
        std::cin >> temp;
        info.push_back(temp);
    }
      std::vector<string> afterSort = getInfoSort(info);
     for (std::vector<string>::iterator it = afterSort.begin();
         it != afterSort.end();
         ++it) {
        std::cout << *it << std::endl;
    }
    return 0;
}
 