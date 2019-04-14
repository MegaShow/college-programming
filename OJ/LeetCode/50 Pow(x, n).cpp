class Solution {
public:
    double myPow(double x, int n) {
        if (abs(x) < 1e-6) return 0;
        if (n == 0) return 1;
        double res = 1;
        while (n) {
            if (n % 2 == 1) res = res * x;
            else if (n % 2 == -1) res = res / x;
            x = x * x;
            n = n / 2;
        }
        return res;
    }
};
