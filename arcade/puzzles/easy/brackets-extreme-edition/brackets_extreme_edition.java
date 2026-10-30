import java.util.*;
class Solution {
   public static void main(String args[]) {
      Scanner in = new Scanner(System.in);
      String expression = in.next();

      Map<Character, Character> pairs = Map.of('(', ')', '{', '}', '[', ']');
      Deque<Character> stack = new ArrayDeque<>();

      for (char c : expression.toCharArray()) { 
         if (!pairs.containsKey(c) && !pairs.containsValue(c)) {
            continue;
         }
         if (pairs.containsKey(c)) {
            stack.push(c);
         } else if (stack.isEmpty() || pairs.get(stack.pop()) != c) {
            System.out.println("false");
            return;
         }
      }
      System.out.println(stack.isEmpty() ? "true" : "false");
   }
}
