// Solution 1
class Solution {
public:
    int candy(vector<int>& ratings) {
        int num[ratings.size()], sum = 0;
        for (int i = 0; i < ratings.size(); i++) {
            if (i == 0 || ratings[i-1] >= ratings[i]) {
                num[i] = 1;
            } else {
                num[i] = num[i-1] + 1;
            }
        }
        for (int i = ratings.size() - 1; i >= 0; i--) {
            if (i + 1 < ratings.size() && ratings[i] > ratings[i+1]) {
                num[i] = max(num[i], num[i+1] + 1);
            }
            sum += num[i];
        }
        return sum;
    }
};

// Solution 2
class Solution {
public:
    int candy(vector<int>& ratings) {
        int start = 0, sum = 0;
        while (start < ratings.size()) {
            int up = 0, down = 0;
            while (start + 1 < ratings.size() && ratings[start] < ratings[start+1]) {
                start++;
                up++;
            }
            while (start + 1 < ratings.size() && ratings[start] > ratings[start+1]) {
                start++;
                down++;
            }
            if (up == 0 && down == 0) {
                sum += 1;
                start++;
                continue;
            }
            sum += (1+up)*up/2 + (max(up, down)+1) + (2+down)*(down-1)/2;
        }
        return sum;
    }
};
