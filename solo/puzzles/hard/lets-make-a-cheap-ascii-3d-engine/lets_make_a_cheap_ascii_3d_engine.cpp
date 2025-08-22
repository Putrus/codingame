#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
   int x, y, a;
   std::cin >> x >> y >> a;
   std::cin.ignore();
   int n;
   std::cin >> n;
   std::cin.ignore();
   for (int i = 0; i < n; i++) 
   {
      std::string row;
      std::getline(std::cin, row);
   }

   std::cout << "answer" << std::endl;
}