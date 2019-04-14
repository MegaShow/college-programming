class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        size = nums.size();
        buildMaxHeap(nums);
        for (int i = 0; i < k - 1; i++) {
            swap(nums[0], nums[--size]);
            maxHeapify(nums, 0);
        }
        return nums[0];
    }

private:
    int size;

    void maxHeapify(vector<int>& nums, int root) {
        int largest = root, lhs = root * 2 + 1, rhs = root * 2 + 2;
        if (lhs < size && nums[lhs] > nums[largest]) largest = lhs;
        if (rhs < size && nums[rhs] > nums[largest]) largest = rhs;
        if (largest != root) {
            swap(nums[largest], nums[root]);
            maxHeapify(nums, largest);
        }
    }

    void buildMaxHeap(vector<int>& nums) {
        for (int i = size / 2 - 1; i >= 0; i--) {
            maxHeapify(nums, i);
        }
    }
};
