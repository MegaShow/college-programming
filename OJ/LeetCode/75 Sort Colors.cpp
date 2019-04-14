class Solution {
public:
    void sortColors(vector<int>& nums) {
        int p = 1, lhs = 0, rhs = nums.size() - 1, mid = 0;
        while (mid <= rhs) {
            if (nums[mid] < p) {
                swap(nums[lhs], nums[mid]);
                lhs++;
                mid++;
            } else if (nums[mid] > p) {
                swap(nums[mid], nums[rhs]);
                rhs--;
            } else {
                mid++;
            }
        }
    }
};
