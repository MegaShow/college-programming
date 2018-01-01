public class Solution {
    public int DominantIndex(int[] nums) {
        var sorted_set = new SortedSet<int>();
        var max = 0;
        for (int i = 1; i < nums.Length; i++) {
            if (nums[i] > nums[max]) {
                sorted_set.Add(nums[max]);
                max = i;
            } else {
                sorted_set.Add(nums[i]);
            }
        }
        return nums[max] >= 2 * sorted_set.Max ? max : -1;
    }
}
