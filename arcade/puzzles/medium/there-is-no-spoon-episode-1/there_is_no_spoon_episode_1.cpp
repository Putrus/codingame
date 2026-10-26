#include <iostream>
#include <string>
#include <vector>

int main()
{
   int width;
   std::cin >> width;
   std::cin.ignore();
   int height;
   std::cin >> height;
   std::cin.ignore();
   std::vector<std::string> grid;
   for (int i = 0; i < height; i++)
   {
      std::string line;
      std::getline(std::cin, line);
      grid.push_back(line);
   }

   for (int i = 0; i < height; ++i)
   {
      for (int j = 0; j < width; ++j)
      {
         if (grid[i][j] == '.')
         {
            continue;
         }
         std::cout << j << ' ' << i;
         
         for (int x = j + 1; x <= width; ++x)
         {
            if (x == width)
            {
               std::cout << " -1 -1";
               break;
            }
            
            if (grid[i][x] == '0')
            {
               std::cout << ' ' << x << ' ' << i;
               break;
            }
         }

         for (int y = i + 1; y <= height; ++y)
         {
            if (y == height)
            {
               std::cout << " -1 -1";
               break;
            }

            if (grid[y][j] == '0')
            {
               std::cout << ' ' << j << ' ' << y;
               break;
            }
         }

         std::cout << std::endl;
      }
   }
}
