public class Solution {
    public int HammingDistance(int x, int y) {
        int z = x ^ y;
        int count = 0;
        while (z != 0) {
            z &= (z - 1);
            count++;
        }
        return count;
    }
}
