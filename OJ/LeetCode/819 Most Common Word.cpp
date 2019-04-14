class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        map<string, int> m;
        for (auto &s: banned) {
            m.insert(make_pair(s, -1));
        }
        string word, maxWord;
        int maxNum = 0;
        for (int i = 0; i <= paragraph.size(); i++) {
            char c = i == paragraph.size() ? ' ' : paragraph[i];
            if (c == ' ' || c == '!' || c == '?' || c == '\'' || c == ',' || c == ';' || c == '.') {
                if (word.size() && m[word] != -1) {
                    m[word]++;
                    if (m[word] > maxNum) {
                        maxWord = word;
                        maxNum = m[word];
                    }
                }
                word.clear();
            } else {
                if (c >= 'A' && c <= 'Z') {
                    word += (c - 'A' + 'a');
                } else {
                    word += c;
                }
            }
        }
        return maxWord;
    }
};
