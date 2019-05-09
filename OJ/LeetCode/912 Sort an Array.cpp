class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, nums.size());
        return nums;
    }

private:
    void quickSort(vector<int>& nums, int start, int end) {
        if (start >= end) return;
        int val = nums[start], l = start, r = end - 1;
        while (l < r) {
            while (l < r && nums[r] > val) {
                r--;
            }
            if (l < r) nums[l++] = nums[r];
            while (l < r && nums[l] < val) {
                l++;
            }
            if (l < r) nums[r--] = nums[l];
        }
        nums[l] = val;
        quickSort(nums, start, l);
        quickSort(nums, l + 1, end);
    }
};
