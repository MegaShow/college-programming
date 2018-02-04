// 779. K-th Symbol in Grammar
public class Solution {
  public int KthGrammar(int N, int K) {
    int sym = 0, pos = 1 << (N - 1);
    K--;
    for (int i = 2; i <= N; i++) {
      if (pos / 2 <= K) {
        pos /= 2;
        K -= pos;
        sym = 1 - sym;
      } else {
        pos /= 2;
      }
      Console.WriteLine($"{sym} - {pos} - {K}");
    }
    return sym;
  }
}
