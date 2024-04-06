#include <iostream>
#include <string>

int main()
{
   int closest = 99999;
   int n; // the number of temperatures to analyse
   std::cin >> n; std::cin.ignore();
   for (int i = 0; i < n; i++) {
      int t; // a temperature expressed as an integer ranging from -273 to 5526
      std::cin >> t; std::cin.ignore();
      if (std::abs(t) < std::abs(closest) || (std::abs(t) == std::abs(closest) && t > 0))
      {
         closest = t;
      }
   }

   if (closest == 99999)
   {
      closest = 0;
   }
   std::cout << closest << std::endl;
}