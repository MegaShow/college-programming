// 762. Prime Number of Set Bits in Binary Representation
public class Solution {
  public int CountPrimeSetBits(int L, int R) {
    bool[] isPrime = new bool[33];
    for (int i = 2; i < 33; i++) {
      int sqrtVal = (int)Math.Sqrt(i);
      bool flag = true;
      for (int j = 2; j <= sqrtVal && flag; j++) {
        if (i % j == 0) flag = false;
      }
      isPrime[i] = flag;
    }
    for (int i = 1; i <= 32; i++) {
      Console.WriteLine($"{i} => {isPrime[i]}");
    }
    int val = 0;
    for (int i = L; i <= R; i++) {
      if (isPrime[numberOfSetBits(i)]) val++;
    }
    return val;
  }

  public int numberOfSetBits(int i) {
     // Java: use >>> instead of >>
     // C or C++: use uint32_t
     i = i - ((i >> 1) & 0x55555555);
     i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
     return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
  }
}
