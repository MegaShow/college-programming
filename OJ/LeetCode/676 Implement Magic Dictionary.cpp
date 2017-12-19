class MagicDictionary {
public:
    map<int, vector<string>> m;
    
    /** Initialize your data structure here. */
    MagicDictionary() {
        
    }
    
    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        for (auto &i : dict) {
            m[i.length()].push_back(i);
        }
    }
    
    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(string word) {
        int len = word.length();
        for (auto &i : m[len]) {
            int count = 0;
            for (int k = 0; k < len; k++) {
                if (i[k] == word[k]) {
                    count++;
                }
            }
            if (count + 1 == len) {
                return true;
            }
        }
        return false;
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary obj = new MagicDictionary();
 * obj.buildDict(dict);
 * bool param_2 = obj.search(word);
 */
