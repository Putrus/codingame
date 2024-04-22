#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
   int n;
   std::cin >> n; std::cin.ignore();
   for (int i = 0; i < n; i++)
   {
      std::string line;
      getline(std::cin, line);

      int result = 0;
      for (int j = 0; j < line.size(); ++j)
      {
         std::string sub = line.substr(j, 3);
         if (sub[0] == 'f' || (sub.size() == 2 && sub[1] == 'f'))
         {
            ++result;
            j += 2;
         }
      }
      std::cout << result << std::endl;
   }
}