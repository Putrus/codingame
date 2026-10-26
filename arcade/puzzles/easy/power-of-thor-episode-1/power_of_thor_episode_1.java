import java.util.*;
import java.io.*;
import java.math.*;

class Player {

   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      int lightX = in.nextInt(); // the X position of the light of power
      int lightY = in.nextInt(); // the Y position of the light of power
      int initialTx = in.nextInt(); // Thor's starting X position
      int initialTy = in.nextInt(); // Thor's starting Y position
      int tx = initialTx;
      int ty = initialTy;
      // game loop
      while (true) {
         int remainingTurns = in.nextInt(); // The remaining amount of turns Thor can move. Do not remove this line.

         if (lightY < ty)
         {
            System.out.print("N");
            --ty;
         }
         else if (lightY > ty)
         {
            System.out.print("S");
            ++ty;
         }

         if (lightX < tx)
         {
            System.out.print("W");
            --tx;
         }
         else if (lightX > tx)
         {
            System.out.print("E");
            ++tx;
         }
         System.out.println("");
      }
   }
}
