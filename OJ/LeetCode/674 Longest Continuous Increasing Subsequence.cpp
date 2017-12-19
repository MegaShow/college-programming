class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int var = 0, max = 0, num = 0;
        for (auto &i : nums) {
            if (i <= num) {
                if (var > max) {
                    max = var;
                }
                var = 1;
                num = i;
            } else {
                num = i;
                var++;
            }
        }
        return (var > max ? var : max);
    }
};
