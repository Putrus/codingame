import java.util.*;

class Solution {
   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      int N = in.nextInt();
      if (in.hasNextLine()) {
         in.nextLine();
      }
      for (int i = 0; i < N; i++) {
         String x = in.nextLine();
         String number = x;
         long newNumber = 0;
         Set<String> history = new HashSet<>();
         while (newNumber != 1 && !history.contains(number)) {
            history.add(number);
            newNumber = 0;
            for (int j = 0; j < number.length(); j++) {
               long digit = number.charAt(j) - '0';
               newNumber += digit * digit;
            }
            number = String.valueOf(newNumber);
         }
         if (newNumber == 1) {
            System.out.println(x + " :)");
         } else {
            System.out.println(x + " :(");
         }
      }
   }
}
