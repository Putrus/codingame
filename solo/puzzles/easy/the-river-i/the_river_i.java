import java.util.*;

class Solution {

   public static long digitsSum(long n) {
      long sum = 0;
      while (n > 0) {
         sum += n % 10;
         n /= 10;
      }
      return sum;
   }

   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      long r1 = in.nextLong();
      long r2 = in.nextLong();

      while (r1 != r2) {
         if (r1 < r2) {
            r1 += digitsSum(r1);
         } else {
            r2 += digitsSum(r2);
         }
      }

      System.out.println(r1);
   }
}