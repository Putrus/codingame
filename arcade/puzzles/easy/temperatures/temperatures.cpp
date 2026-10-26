#include <iostream>
#include <limits>

int main()
{
   int n, t, closest = std::numeric_limits<int>::max();
   std::cin >> n; std::cin.ignore();
   for (int i = 0; i < n; ++i)
   {
      std::cin >> t; std::cin.ignore();
      if (std::abs(t) < std::abs(closest) || (std::abs(t) == std::abs(closest) && t > 0))
      {
         closest = t;
      }
   }

   if (closest == std::numeric_limits<int>::max())
   {
      closest = 0;
   }
   std::cout << closest << std::endl;
}