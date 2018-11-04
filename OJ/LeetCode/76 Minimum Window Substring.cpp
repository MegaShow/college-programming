// Solution 1
class Solution {
public:
    string minWindow(string s, string t) {
        map<char, int> remain;
        for (int i = 0; i < t.length(); i++) {
            remain[t[i]]++;
        }
        int start = 0, end = 0, pass = 0, left = 0, min = INT_MAX;
        while (start < s.length() && end <= s.length()) {
            if (pass != t.length()) {
                if (end == s.length()) {
                    break;
                }
                remain[s[end]]--;
                if (remain[s[end]] >= 0) {
                    pass++;
                }
                end++;
            } else {
                if (min > end - start) {
                    left = start;
                    min = end - start;
                }
                remain[s[start]]++;
                if (remain[s[start]] > 0) {
                    pass--;
                }
                start++;
            }
        }
        return min == INT_MAX ? "" : s.substr(left, min);
    }
};

// Solution 2
class Solution {
public:
    string minWindow(string s, string t) {
        map<char, int> remain;
        vector<pair<char, int> > filter;
        for (int i = 0; i < t.length(); i++) {
            remain[t[i]]++;
        }
        for (int i = 0; i < s.length(); i++) {
            if (remain.count(s[i])) {
                filter.push_back(make_pair(s[i], i));
            }
        }
        int start = 0, end = 0, pass = 0, left = 0, min = INT_MAX;
        while (start < filter.size() && end <= filter.size()) {
            if (pass != t.length()) {
                if (end == filter.size()) {
                    break;
                }
                remain[filter[end].first]--;
                if (remain[filter[end].first] >= 0) {
                    pass++;
                }
                end++;
            } else {
                if (min > filter[end-1].second - filter[start].second + 1) {
                    left = filter[start].second;
                    min = filter[end-1].second - filter[start].second + 1;
                }
                remain[filter[start].first]++;
                if (remain[filter[start].first] > 0) {
                    pass--;
                }
                start++;
            }
        }
        return min == INT_MAX ? "" : s.substr(left, min);
    }
};
