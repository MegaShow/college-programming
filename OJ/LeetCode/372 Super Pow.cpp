class Solution {
public:
    int superPow(int a, vector<int>& b) {
        int res = 1;
        for (int i = 0; i < b.size(); i++) {
            res = pow(res, 10) * pow(a, b[i]) % 1337;
        }
        return res;
    }

private:
    int pow(int a, int b) {
        int res = 1;
        a = a % 1337;
        while (b) {
            if (b & 1) {
                res = res * a % 1337;
            }
            a = a * a % 1337;
            b >>= 1;
        }
        return res;
    }
};
