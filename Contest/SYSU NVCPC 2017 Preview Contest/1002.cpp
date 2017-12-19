// 1002
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


int main(){
    int case__num = 0;
    scanf("%d", &case__num);
    for(int i = 0; i < case__num; i++){
        vector<int> my_width;
        vector<int> my_height;
        int max_width, max_height;
        scanf("%d%d", &max_width, &max_height);
        int tower_num;
        scanf("%d", &tower_num);
        if (tower_num) {
            for(int j = 0; j < tower_num; j++){
              int width, height;
              scanf("%d%d", &width, &height);
              my_width.push_back(width);
              my_height.push_back(height);
            }
            sort(my_width.begin(), my_width.end());
            sort(my_height.begin(), my_height.end());
            int count = my_width.size();
            vector<int> d_width;
            vector<int> d_height;
            for(int j = 0; j < count; j++){
                if(j == 0){
                    d_width.push_back(my_width[j] - 1);
                }
                else{
                    d_width.push_back(my_width[j] - my_width[j-1] - 1);
                }
                if(j == count - 1){
                    d_width.push_back(max_width - my_width[j]);
                }
            }
            count = my_height.size();
            for(int j = 0; j < count; j++){
                if(j == 0){
                    d_height.push_back(my_height[j] - 1);
                }
                else{
                    d_height.push_back(my_height[j] - my_height[j-1] - 1);
                }
                if(j == count - 1){
                    d_height.push_back(max_height - my_height[j]);
                }
            }
            sort(d_width.begin(), d_width.end());
            sort(d_height.begin(), d_height.end());
            printf("%d\n", d_height[d_height.size() - 1] * d_width[d_width.size() - 1]);
        } else {
            printf("%d\n", max_height * max_width);
        }
    }
}
