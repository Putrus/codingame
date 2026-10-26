#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
   int n;
   std::cin >> n; std::cin.ignore();
   std::vector<int> heights;
   for (int i = 0; i < n; i++)
   {
      int height;
      std::cin >> height; std::cin.ignore();
      heights.push_back(height);
   }

   int best = 0;
   for (int i = 1; i < heights.size() - 1; ++i)
   {
      int middle = heights[i];
      int left = *std::min_element(heights.begin(), heights.begin() + i);
      int right = *std::min_element(heights.begin() + i, heights.end());
      if (left >= middle || right >= middle)
      {
         continue;
      }
      int score = 2 * middle - left - right;
      if (score > best)
      {
         best = score;
      }
   }

   std::cout << best << std::endl;
}
