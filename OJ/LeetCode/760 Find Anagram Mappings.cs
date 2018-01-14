public class Solution {
  public int[] AnagramMappings(int[] A, int[] B) {
    var from_val_to_index = new Dictionary<int, int>();
    for (int i = 0; i < B.Length; i++) {
      if (from_val_to_index.ContainsKey(B[i]) == false) {
        from_val_to_index.Add(B[i], i);
      }
    }
    var arr = new int[A.Length];
    for (int i = 0; i < A.Length; i++) {
      arr[i] = from_val_to_index[A[i]];
    }
    return arr;
  }
}
