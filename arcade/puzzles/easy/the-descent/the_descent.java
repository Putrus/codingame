import java.util.*;
import java.io.*;
import java.math.*;

class Player {

   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);

      // game loop
      while (true) {
         int max = 0;
         int id = 0;
         for (int i = 0; i < 8; i++) {
            int mountain_h = in.nextInt();
            if (mountain_h > max)
            {
                max = mountain_h;
                id = i;
            }
         }

         System.out.println(id);
      }
   }
}
