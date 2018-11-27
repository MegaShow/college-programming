// Solution 1
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.length() + s2.length() != s3.length()) {
            return false;
        }
        bool dp[s1.length()+1][s2.length()+1];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = true;
        for (int i = 0; i <= s1.length(); i++) {
            dp[i][0] = s1.substr(0, i) == s3.substr(0, i);
        }
        for (int j = 0; j <= s2.length(); j++) {
            dp[0][j] = s2.substr(0, j) == s3.substr(0, j);
        }
        for (int i = 1; i <= s1.length(); i++) {
            for (int j = 1; j <= s2.length(); j++) {
                dp[i][j] = (s1[i-1] == s3[i+j-1] && dp[i-1][j])
                    || (s2[j-1] == s3[i+j-1] && dp[i][j-1]);
            }
        }
        return dp[s1.length()][s2.length()];
    }
};

// Solution 2
class Solution {
private:
    int getRepeats(string &str, int index) {
        int res = 1;
        for (int i = index + 1; str[i] == str[index] && i < str.length(); i++) {
            res++;
        }
        return res;
    }

public:
    bool isInterleave(string s1, string s2, string s3) {
        if (s1.length() + s2.length() != s3.length()) {
            return false;
        }
        stack<pair<int, int>> s;
        for (int i = 0, j = 0; i < s1.length() || j < s2.length();) {
            if (s1[i] == s3[i+j] && s2[j] != s3[i+j]) {
                i++;
            } else if (s1[i] != s3[i+j] && s2[j] == s3[i+j]) {
                j++;
            } else if (s1[i] != s3[i+j] && s2[j] != s3[i+j]) {
                if (s.size() == 0) {
                    return false;
                } else {
                    i = s.top().first;
                    j = s.top().second;
                    s.pop();
                }
            } else {
                int r1 = getRepeats(s1, i);
                int r2 = getRepeats(s2, j);
                int r3 = getRepeats(s3, i + j);
                if (r1 + r2 == r3) {
                    i += r1;
                    j += r2;
                } else if (r3 >= r1 && r3 < r2) {
                    i += r1;
                    j += r3 - r1;
                } else if (r3 >= r2 && r3 < r1) {
                    i += r3 - r2;
                    j += r2;
                } else {
                    if (r1 + r2 < r3) {
                        if (s.size() == 0) {
                            return false;
                        } else {
                            i = s.top().first;
                            j = s.top().second;
                            s.pop();
                        }
                    } else {
                        s.push(make_pair(i, j + r2));
                        i += r1;
                    }
                }
            }
        }
        return true;
    }
};
