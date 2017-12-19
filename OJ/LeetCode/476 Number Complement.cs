public class Solution {
    public int FindComplement(int num) {
        int index = 0;
        while ((num >> index) != 0) {
            index ++;
        }
        return (1 << index) - 1 - num;
    }
}
