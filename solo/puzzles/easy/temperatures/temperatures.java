import java.util.*;
import java.io.*;
import java.math.*;

class Solution {

   public static void main(String args[]) {
      int closest = 99999;
      Scanner in = new Scanner(System.in);
      int n = in.nextInt();
      for (int i = 0; i < n; i++) {
         int t = in.nextInt();
         if (Math.abs(t) < Math.abs(closest) || (Math.abs(t) == Math.abs(closest) && t > 0))
         {
            closest = t;
         }
      }

      if (closest == 99999)
      {
         closest = 0;
      }
      System.out.println(closest);
   }
}
