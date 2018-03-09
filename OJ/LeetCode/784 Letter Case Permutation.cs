// 784. Letter Case Permutation
public class Solution {
  public IList<string> LetterCasePermutation(string S) {
    Queue<string> queue = new Queue<string>();
    S = S.ToLower();
    queue.Enqueue(S);
    for (int i = 0; i < S.Length; i++) {
      if (S[i] < 'a' || S[i] > 'z') continue;
      for (int j = queue.Count(); j > 0; j--) {
        char[] arr = queue.Dequeue().ToCharArray();
        queue.Enqueue(new string(arr));
        arr[i] = Char.ToUpper(arr[i]);
        queue.Enqueue(new string(arr));
      }
    }
    return queue.ToArray();
  }
}
