public class Solution {
    public int LengthOfLongestSubstring(string s) {
        int max = 0, val = 0, index = 0;
        int[] arr = Enumerable.Repeat(-1, 128).ToArray();
        for (int i = 0; i < s.Length; i++) {
            if (arr[s[i]] != -1) {
                if (max < val) {
                    max = val;
                }
                val = i - arr[s[i]] - 1;
                int k = arr[s[i]];
                for (int j = index; j < k; j++) {
                    arr[s[j]] = -1;
                }
                index = k + 1;
            }
            val++;
            arr[s[i]] = i;
        }
        return (max > val ? max : val);
    }
}
