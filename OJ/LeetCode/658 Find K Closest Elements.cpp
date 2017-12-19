class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        multimap<int, int> m;
        for (auto &y : arr) {
            m.insert(make_pair(abs(y-x), y));
        }
        vector<int> v;
        auto it = m.begin();
        for (int i = 0; i < k; i++, it++) {
            v.push_back(it->second);
        }
        stable_sort(v.begin(), v.end());
        return v;
    }
};
