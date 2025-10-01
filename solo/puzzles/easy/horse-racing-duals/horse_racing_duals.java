import java.util.*;
import java.io.*;
import java.math.*;

class Solution {

   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      int N = in.nextInt();
      List<Integer> arr = new ArrayList<Integer>();
      for (int i = 0; i < N; i++) {
         int pi = in.nextInt();
         arr.add(pi);
      }
        
      Collections.sort(arr);

      int min = 10000000;
      for (int i = 0; i < arr.size() - 1; ++i)
      {
         if (arr.get(i + 1) - arr.get(i) < min)
         {
            min = arr.get(i + 1) - arr.get(i);
         }
      }
      System.out.println(min);
   }
}
