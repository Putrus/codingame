import java.util.*;

class Solution {

   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      char[] b = in.nextLine().toCharArray();

      long longest = 0;
      for (int pos = 0; pos < b.length; pos++) {
         long ones = 1;
         //left
         for (int i = pos - 1; i >= 0; i--) {
            if (b[i] == '1') {
               ones++;
            } else {
               break;
            }
         }
         //right
         for (int i = pos + 1; i < b.length; i++) {
            if (b[i] == '1') {
               ones++;
            } else {
               break;
            }
         }

         if (longest < ones) {
            longest = ones;
         }
      }

      System.out.println(longest);
   }
}
