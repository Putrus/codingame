import java.util.*;

class Solution {

    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        List<Integer> arr = new ArrayList<Integer>();
        for (int i = 0; i < n; i++) {
            int a = in.nextInt();
            arr.add(a);
        }

        int left = 0;
        int right = arr.size() - 1;

        int maxArea = 0;
        while (left != right)
        {
            int area = Math.min(arr.get(left), arr.get(right)) * (right - left);
            if (area > maxArea)
            {
                maxArea = area;
            }

            if (arr.get(left) < arr.get(right))
            {
                ++left;
            }
            else
            {
                --right;
            }
        }

        System.out.println(maxArea);
    }
}
