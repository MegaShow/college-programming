public class Solution {
    public int LongestConsecutive(int[] nums) {
        var ss = new SortedSet<int>(nums);
        int max = 0, count = 0, last_x = 0;
        bool flag = true;
        foreach (var x in ss) {
            if (flag || x != last_x + 1) {
                flag = false;
                if (count > max) {
                    max = count;
                }
                count = 0;
            }
            count++;
            last_x = x;
        }
        return max > count ? max : count;
    }
}
