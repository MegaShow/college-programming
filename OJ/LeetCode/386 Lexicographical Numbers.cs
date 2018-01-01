public class Solution {
  public IList<int> LexicalOrder(int n) {
    IList<int> li = new List<int>();
    int val = 1;
    while (val <= n) {
      li.Add(val);
      if (val * 10 <= n) val *= 10;
      else {
        val++;
        if (val > n) val /= 10;
      }
    }
    return li;
  }
}