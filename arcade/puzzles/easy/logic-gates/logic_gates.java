import java.util.*;

class Solution {
   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      int n = in.nextInt();
      int m = in.nextInt();
      int length = 0;
      HashMap<String, String> inputs = new HashMap<>();
      for (int i = 0; i < n; i++) {
         String inputName = in.next();
         String inputSignal = in.next();
         length = inputSignal.length();
         inputs.put(inputName, inputSignal);
      }
      for (int i = 0; i < m; i++) {
         String outputName = in.next();
         String type = in.next();
         String inputName1 = in.next();
         String inputName2 = in.next();
         System.out.print(outputName + " ");
         char[] input1 = inputs.get(inputName1).toCharArray();
         char[] input2 = inputs.get(inputName2).toCharArray();
         for (int j = 0; j < length; j++) {
            boolean a = input1[j] == '-';
            boolean b = input2[j] == '-';

            boolean result = switch (type) {
               case "AND" -> a && b;
               case "OR" -> a || b;
               case "XOR" -> a ^ b;
               case "NAND" -> !(a && b);
               case "NOR" -> !(a || b);
               case "NXOR" -> a == b;
               default -> false;
            };

            System.out.print(result ? '-' : '_');
         }
         System.out.println("");
      }
   }
}
