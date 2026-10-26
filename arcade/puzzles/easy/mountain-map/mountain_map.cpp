#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
   int n; // the number of mountains
   std::cin >> n; std::cin.ignore();
   int max_height = 0;
   std::vector<int> heights(n);
   for (int i = 0; i < n; i++)
   {
      int height; // height of the mountain
      std::cin >> height; std::cin.ignore();
      heights[i] = height;
      if (height > max_height)
      {
         max_height = height;
      }
   }

   for (int i = max_height; i > 0; --i)
   {
      for (int k = 0; k < heights.size(); ++k)
      {
         int height = heights[k];
         if (height < i)
         {
            bool higher_exist = false;
            for (int j = k + 1; j < heights.size(); ++j)
            {
               if (heights[j] >= i)
               {
                  higher_exist = true;
                  break;
               }
            }
            if (higher_exist)
            {
               for (int j = 0; j < height * 2; ++j)
               {
                  std::cout << ' ';
               }
            }
         }
         else
         {
            for (int j = 0; j < height - (height - i) - 1; ++j)
            {
               std::cout << ' ';
            }
            std::cout << '/';
            for (int j = 0; j < (height - i) * 2; ++j)
            {
               std::cout << ' ';
            }
            std::cout << '\\';

            bool higher_exist = false;
            for (int j = k + 1; j < heights.size(); ++j)
            {
               if (heights[j] >= i)
               {
                  higher_exist = true;
                  break;
               }
            }
            if (higher_exist)
            {
               for (int j = 0; j < height - (height - i) - 1; ++j)
               {
                  std::cout << ' ';
               }
            }
         }
      }
      std::cout << std::endl;
   }
}