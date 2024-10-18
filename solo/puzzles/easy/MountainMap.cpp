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

   for (int height : heights)
   {
      
   }
   std::cout << "answer" << std::endl;
}