class KthLargest {
public:
    KthLargest(int k, vector<int>& nums): v(k, INT_MIN) {
        int size = nums.size();
        // build min heap
        for (int i = size / 2 - 1; i >= 0; i--) {
            maxHeapify(nums, i, size);
        }
        for (int i = 0; i < k && i < nums.size(); i++) {
            v[i] = nums[0];
            swap(nums[0], nums[--size]);
            maxHeapify(nums, 0, size);
        }
    }

    int add(int val) {
        for (int i = v.size() - 1; i >= 0; i--) {
            if (val >= v[i]) {
                if (i < v.size() - 1) v[i + 1] = v[i];
                v[i] = val;
            } else {
                break;
            }
        }
        return v[v.size() - 1];
    }

private:
    vector<int> v;

    void maxHeapify(vector<int>& nums, int root, int size) {
        int largest = root, lhs = root * 2 + 1, rhs = root * 2 + 2;
        if (lhs < size && nums[lhs] > nums[largest]) largest = lhs;
        if (rhs < size && nums[rhs] > nums[largest]) largest = rhs;
        if (largest != root) {
            swap(nums[largest], nums[root]);
            maxHeapify(nums, largest, size);
        }
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
