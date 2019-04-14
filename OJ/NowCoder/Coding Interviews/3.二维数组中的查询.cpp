class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        if (array.size() == 0 || array[0].size() == 0) return false;
        for (int i = array.size() - 1; i >= 0; i--) {
            if (array[i][0] > target) continue;
            for (int j = 0; j < array.size(); j++) {
                if (array[i][j] == target) return true;
            }
        }
        return false;
    }
};
