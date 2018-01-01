// 754. Reach a Number
public class Solution {
  public int ReachNumber(int target) {
    target = Math.Abs(target);
    int step = 0, position = 0;
    while (position < target) {
      step++;
      position += step;
    }
    if (target == position || (position - target) % 2 == 0) return step;
    if (step % 2 == 0) return step + 1;
    return step + 2;
  }
}
