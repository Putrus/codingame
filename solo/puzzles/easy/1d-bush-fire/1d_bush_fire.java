import java.util.*;

class Solution {

   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      int N = in.nextInt();
      if (in.hasNextLine()) {
         in.nextLine();
      }
      
      for (int i = 0; i < N; i++) {
         String line = in.nextLine();

         int result = 0;
         for (int j = 0 ; j < line.length(); j++) {
            String sub = line.substring(j, Math.min(j + 3, line.length()));
            if (sub.charAt(0) == 'f' || (sub.length() == 2 && sub.charAt(1) == 'f')) {
               result++;
               j += 2;
            }
         }
         System.out.println(result);
      }
   }
}