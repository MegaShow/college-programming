class Solution {
public:
    bool isScramble(string s1, string s2) {
        if (s1 == s2) {
            return true;
        }
        int count[26] = {0};
        for (int i = 0; i < s1.length(); i++) {
            count[s1[i]-'a']++;
        }
        for (int i = 0; i < s2.length(); i++) {
            count[s2[i]-'a']--;
            if (count[s2[i]-'a'] < 0) {
                return false;
            }
        }
        for (int i = 1; i < s1.length(); i++) {
            if (isScramble(s1.substr(0, i), s2.substr(0, i)) && isScramble(s1.substr(i), s2.substr(i))) {
                return true;
            }
            if (isScramble(s1.substr(0, i), s2.substr(s2.length()-i)) && isScramble(s1.substr(i), s2.substr(0, s2.length()-i))) {
                return true;
            }
        }
        return false;
    }
};
