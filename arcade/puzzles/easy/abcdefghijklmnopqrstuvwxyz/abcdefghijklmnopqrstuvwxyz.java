import java.util.*;

class Solution {

   public static char[][] emptyGrid(int n, int m) {
      char[][] array = new char[n][m];

      for (int i = 0; i < n; i++) {
         Arrays.fill(array[i], '-');
      }

      return array;
   }

   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      int n = in.nextInt();
      char[][] grid = new char[n][];

      for (int i = 0; i < n; i++) {
         grid[i] = in.next().toCharArray();
      }

      for (int i = 0; i < grid.length; i++) {
         for (int j = 0; j < grid[i].length; j++) {
            if (grid[i][j] == 'a') {
               char[][] resultGrid = emptyGrid(grid.length, grid[i].length);
               int y = i;
               int x = j;
               while (true) {
                  resultGrid[y][x] = grid[y][x];
                  if (grid[y][x] == 'z') {
                     for (int k = 0; k < grid.length; k++) {
                        System.out.println(resultGrid[k]);
                     }
                     return;
                  }
                  char nextLetter = (char)(grid[y][x] + 1);
                  if (x - 1 >= 0 && grid[y][x - 1] == nextLetter) {
                     x--;
                  } else if (y - 1 >= 0 && grid[y - 1][x] == nextLetter) {
                     y--;
                  } else if (x + 1 < grid[y].length && grid[y][x + 1] == nextLetter) {
                     x++;
                  } else if (y + 1 < grid.length && grid[y + 1][x] == nextLetter) {
                     y++;
                  } else {
                     break;
                  }
               }
            }
         }
      }
   }
}
