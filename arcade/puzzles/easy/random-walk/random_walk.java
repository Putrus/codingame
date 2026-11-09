import java.util.*;

class Solution {

   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      long a = in.nextLong();
      long b = in.nextLong();
      long m = in.nextLong();

      int x = 0;
      int y = 0;
      long generation = 0;
      long steps = 0;
      do {
         generation = (a * generation + b) % m;
         int direction = (int)(generation % 4);
         switch (direction) {
            case 0:
               --y;
               break;
            case 1:
               ++y;
               break;
            case 2:
               --x;
               break;
            case 3:
               ++x;
               break;
         }
         ++steps;
      } while (x != 0 || y != 0);

      System.out.println(steps);
   }
}
