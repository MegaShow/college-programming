class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> m;
        for (int i = 0; i < nums.size(); i++) {
            int var = target - nums[i];
            if (m.count(var)) {
                return vector<int>({m[var], i});
            }
            m[nums[i]] = i;
        }
        return vector<int>();
    }
};
