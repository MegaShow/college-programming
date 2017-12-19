public class Solution {
    public IList<int> LexicalOrder(int n) {
        IList<int> li = new List<int>();
        int var = 1;
        for (int i = 0; i < n; i ++) {
            li.Add(var);
            if (var * 10 <= n) {
                var *= 10;
            } else {
                var++;
                if (var % 10 == 0) {
                    var /= 10;
                }
                if (var > n) {
                    var /= 10;
                    var ++;
                }
                while (var % 10 == 0) {
                    var /= 10;
                }
            }
        }
        if (li.Count != n) {
            return null;
        }
        return li;
    }
}
