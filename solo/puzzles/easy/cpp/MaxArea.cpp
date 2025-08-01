#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
   int n;
   std::cin >> n; std::cin.ignore();
   std::vector<int> segments(n);
   for (int i = 0; i < n; i++)
   {
      int a;
      std::cin >> a; std::cin.ignore();
      segments[i] = a;
   }

   int left = 0;
   int right = segments.size() - 1;

   int max_area = 0;
   while (left != right)
   {
      int area = std::min(segments[left], segments[right]) * (right - left);
      if (area > max_area)
      {
         max_area = area;
      }

      if (segments[left] < segments[right])
      {
         ++left;
      }
      else
      {
         --right;
      }
   }
   std::cout << max_area << std::endl;
}