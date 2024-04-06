#include <iostream>
#include <string>
#include <vector>

int main()
{
   int w;
   int h;
   std::cin >> w >> h; std::cin.ignore();
   std::vector<std::string> diagram;
   for (int i = 0; i < h; i++)
   {
      std::string line;
      std::getline(std::cin, line);
      diagram.push_back(line);
   }

   if (diagram.empty())
   {
      return 0;
   }

   for (size_t start = 0; start < diagram.front().length(); start += 3)
   {
      int j = start;
      for (int i = 1; i < static_cast<int>(diagram.size()); ++i)
      {
         if (j - 1 > 0 && diagram[i][j - 1] == '-')
         {
            j -= 3;
         }
         else if (j + 1 < diagram[i].length() && diagram[i][j + 1] == '-')
         {
            j += 3;
         }
      }
      std::cout << diagram.front()[start] << diagram.back()[j] << std::endl;
   }
}