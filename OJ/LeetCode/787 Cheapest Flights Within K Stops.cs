// 787. Cheapest Flights Within K Stops
public class Solution {
  public int FindCheapestPrice(int n, int[,] flights, int src, int dst, int K) {
    int[,] graph = new int[n, n];
    for (int i = 0; i < flights.Length / 3; i++) {
      graph[flights[i, 0], flights[i, 1]] = flights[i, 2];
    }
    int[] price = new int[n];
    int[] dis = new int[n];
    for (int i = 0; i < n; i++) {
      price[i] = -1;
      dis[i] = -1;
    }
    Queue<int> q = new Queue<int>();
    q.Enqueue(src);
    price[src] = 0;
    while (q.Count() != 0) {
      int nq = q.Dequeue();
      for (int i = 0; i < n; i++) {
        if (graph[nq, i] == 0) continue;
        if (price[i] == -1 && dis[nq] < K) {
          Console.WriteLine($"{price[nq]} + {graph[nq, i]}");
          price[i] = price[nq] + graph[nq, i];
          dis[i] = dis[nq] + 1;
          q.Enqueue(i);
          Console.WriteLine($"If: {i} - {price[i]}");
        } else if (price[i] > price[nq] + graph[nq, i] && dis[nq] < K) {
          price[i] = price[nq] + graph[nq, i];
          dis[i] = dis[nq] + 1;
          q.Enqueue(i);
          Console.WriteLine($"Else If: {i} - {price[i]}");
        }
      }
    }
    return price[dst];
  }
}
