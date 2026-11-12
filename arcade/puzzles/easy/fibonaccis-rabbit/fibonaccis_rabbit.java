import java.util.*;

class Solution {

   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      long F0 = in.nextLong();
      int N = in.nextInt();
      int a = in.nextInt();
      long b = in.nextLong();
      long[] array = new long[N + 1];

      Arrays.fill(array, 0);
      array[0] = F0;

      for (int i = 1; i <= N; ++i) {
         for (int j = a; j <= b; ++j) {
            array[i] += i - j >= 0 ? array[i - j] : 0;
         }
      }
      System.out.println(array[N]);
   }
}
