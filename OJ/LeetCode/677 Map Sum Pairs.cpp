class MapSum {
private:
    map<string, int> m;

public:
    /** Initialize your data structure here. */
    MapSum() {
        
    }
    
    void insert(string key, int val) {
        m[key] = val;
    }
    
    int sum(string prefix) {
        int var = 0;
        for (auto &x: m) {
            bool flag = true;
            for (int i = 0; i < prefix.length(); i++) {
                if (prefix[i] != x.first[i]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                var += x.second;
            }
        }
        return var;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum obj = new MapSum();
 * obj.insert(key,val);
 * int param_2 = obj.sum(prefix);
 */
 