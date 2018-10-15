class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) {
            return s;
        }
        const int round = numRows * 2 - 2;
        string out;
        for (int r = 0; r < numRows; r++) {
            for (int i = r; i < s.size(); i += round) {
                if (r == 0 || r == numRows - 1) {
                    out += s[i];
                } else {
                    out += s[i];
                    if (i/round*round+round-i%round < s.size()) {
                        out += s[i/round*round+round-i%round];
                    }
                }
            }
        }
        return out;
    }
};
