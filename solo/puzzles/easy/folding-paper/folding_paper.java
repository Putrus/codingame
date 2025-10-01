import java.util.*;
import java.io.*;
import java.math.*;

class Solution {

   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      String order = in.nextLine();
      String side = in.nextLine();

      HashMap<Character, Integer> ids = new HashMap<Character, Integer>();
      ids.put('U', 0);
      ids.put('L', 1);
      ids.put('D', 2);
      ids.put('R', 3);
      List<Integer> folding = new ArrayList<Integer>(Collections.nCopies(4, 1));
      for (int i = 0; i < order.length(); ++i)
      {
         Character s = order.charAt(i);
         folding.set((ids.get(s) + 2) % folding.size(), folding.get((ids.get(s) + 2) % folding.size()) + folding.get(ids.get(s)));
         folding.set((ids.get(s) + 1) % folding.size(), folding.get((ids.get(s) + 1) % folding.size()) * 2);
         folding.set((ids.get(s) + 3) % folding.size(), folding.get((ids.get(s) + 3) % folding.size()) * 2);
         folding.set(ids.get(s), 1);
      }

      System.out.println(folding.get(ids.get(side.charAt(0))));
   }
}
