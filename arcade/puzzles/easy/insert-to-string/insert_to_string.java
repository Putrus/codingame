import java.util.*;

class Solution {

   static class Change {
      int col;
      String text;

      Change(int col, String text) {
         this.col = col;
         this.text = text;
      }
   }

   public static void main(String[] args) {
      Scanner in = new Scanner(System.in);
      String s = in.nextLine();
      int changeCount = Integer.parseInt(in.nextLine());

      String[] lines = s.split("\\\\n", -1);

      ArrayList<ArrayList<Change>> changes = new ArrayList<>();

      for (int i = 0; i < lines.length; i++) {
         changes.add(new ArrayList<>());
      }
   
      for (int i = 0; i < changeCount; i++) {
         String rawChange = in.nextLine();

         int firstPipe = rawChange.indexOf('|');
         int lastPipe = rawChange.lastIndexOf('|');

         int line = Integer.parseInt(
            rawChange.substring(0, firstPipe)
         );

         int col = Integer.parseInt(
            rawChange.substring(firstPipe + 1, lastPipe)
         );

         String text = rawChange.substring(lastPipe + 1);

         changes.get(line).add(new Change(col, text));
      }

      StringBuilder result = new StringBuilder();

      for (int i = 0; i < lines.length; i++) {

         ArrayList<Change> lineChanges = changes.get(i);

         lineChanges.sort(
            Comparator.comparingInt(c -> c.col)
         );

         String original = lines[i];
         int lastPos = 0;

         for (Change change : lineChanges) {

            result.append(
               original.substring(lastPos, change.col)
            );

            result.append(change.text);

            lastPos = change.col;
         }

         result.append(original.substring(lastPos));

         if (i < lines.length - 1) {
            result.append("\\n");
         }
      }

      System.out.println(
         result.toString().replace("\\n", "\n")
      );
   }
}
