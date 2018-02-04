// 771. Jewels and Stones
public class Solution {
  public int NumJewelsInStones(string J, string S) {
    int[] isJewel = new int[128];
    foreach (char i in J) {
      isJewel[i] = 1;
    }
    int result = 0;
    foreach (char i in S) {
      result += isJewel[i];
    }
    return result;
  }
}
