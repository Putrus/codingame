import java.util.*;

class Solution {
   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      int valueToReach = in.nextInt();
      int N = in.nextInt();
      ArrayList<int[]> coins = new ArrayList<>();
      List<Integer> counts = new ArrayList<>();
      for (int i = 0; i < N; i++) {
         int count = in.nextInt();
         counts.add(count);
      }
      for (int i = 0; i < N; i++) {
         int value = in.nextInt();
         coins.add(new int[]{value, counts.get(i)});
      }
      coins.sort((a, b) -> Integer.compare(a[0], b[0]));
      int current = 0;
      int result = 0;
      while (current != coins.size() && valueToReach > 0) {
         if (coins.get(current)[1] == 0) {
            current++;
            continue;
         }
         valueToReach -= coins.get(current)[0];
         coins.get(current)[1]--;
         result++;
         System.err.println(valueToReach);
      }
      if (valueToReach > 0) {
         System.out.println("-1");
      } else {
         System.out.println(result);
      }
   }
}
