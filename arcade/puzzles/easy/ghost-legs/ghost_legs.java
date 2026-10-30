import java.util.*;

class Solution {
   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      int W = in.nextInt();
      int H = in.nextInt();
      if (in.hasNextLine()) {
         in.nextLine();
      }
      char[][] grid = new char[H][W];
      for (int i = 0; i < H; i++) {
         String line = in.nextLine();
         grid[i] = line.toCharArray();
      }

      for (int i = 0; i < W; i += 3) {
         char currentLetter = grid[0][i];
         int x = i;
         int y = 1;
         while (y != H - 1) {
            if (x - 1 >= 0 && grid[y][x - 1] == '-') {
               x -= 3;
            } else if (x + 1 < W && grid[y][x + 1] == '-') {
               x += 3;
            }

            y++;
         }
         System.out.println("" + currentLetter + grid[y][x]);
      }
   }
}
