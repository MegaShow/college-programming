// 763. Partition Labels
public class Solution {
  public IList<int> PartitionLabels(string S) {
    int[] end = new int[26];
    for (int i = 0; i < S.Length; i++) {
      end[S[i] - 'a'] = i;
    }
    var list = new List<int>();
    int index = end[S[0] - 'a'], start = 0;
    for (int i = 0; i < S.Length; i++) {
      if (i == index) {
        list.Add(index - start + 1);
        start = index + 1;
        if (start < S.Length) index = end[S[start] - 'a'];
      } else {
        if (end[S[i] - 'a'] > index) index = end[S[i] - 'a'];
      }
    }
    return list;
  }
}
