public class Solution {
    public int ArrayPairSum(int[] nums) {
        Array.Sort(nums);
        int var = 0;
        for (int i = 0; i < nums.Length; i += 2) {
            var += nums[i];
        }
        return var;
    }
}
