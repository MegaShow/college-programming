// 796. Rotate String
public class Solution {
  public bool RotateString(string A, string B) {
    if (A.Length != B.Length) return false;
    for (int i = 0; i < A.Length; i++) {
      if (A[i] != B[0]) continue;
      int j;
      for (j = 0; j + i < A.Length; j++) {
        if (A[j + i] != B[j]) break;
      }
      if (j + i == A.Length) {
        for (int k = 0; k < i; j++, k++) {
          if (A[k] != B[j]) break;
        }
      }
      if (j == A.Length) return true;
    }
    return false;
  }
}
