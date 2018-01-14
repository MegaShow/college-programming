public class Solution {
  public string BoldWords(string[] words, string S) {
    var arr = new Boolean[502];
    for (int t = 0; t < words.Length; t++) {
      for (int i = 0; i < S.Length; i++) {
        int index = S.IndexOf(words[t], i);
        if (index == -1) continue;
        for (int j = 0; j < words[t].Length; j++) {
          arr[j + index] = true;
        }
      }
    }
    string str = String.Empty;
    bool flag = false;
    for (int i = 0; i < S.Length; i++) {
      if (arr[i] && !flag) {
        flag = true;
        str += "<b>" + S[i];
      } else if (!arr[i] && flag) {
        flag = false;
        str += "</b>" + S[i];
      } else {
        str += S[i];
      }
    }
    if (flag) str += "</b>";
    return str;
  }
}
