// 785. Is Graph Bipartite?
public class Solution {
  public bool IsBipartite(IList<IList<int>> graph) {
    int[] color = new int[graph.Count()];
    Queue<int> q = new Queue<int>();
    HashSet<int> hs = new HashSet<int>();
    for (int i = 1; i < graph.Count(); i++) {
      hs.Add(i);
    }
    q.Enqueue(0);
    color[0] = 1;
    while (q.Count() != 0) {
      int n = q.Dequeue();
      foreach (int i in graph[n]) {
        if (color[i] == 0) {
          q.Enqueue(i);
          color[i] = 3 - color[n];
          hs.Remove(i);
        }
        else if (color[i] == color[n]) {
          return false;
        }
      }
      if (q.Count() == 0 && hs.Count() != 0) {
        int tmp = hs.First();
        color[tmp] = 1;
        q.Enqueue(tmp);
        hs.Remove(tmp);
      }
    }
    return true;
  }
}
