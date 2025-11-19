#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
   int w;
   int h;
   std::cin >> w >> h; std::cin.ignore();
   std::vector<std::string> grid;
   bool rectangle = true;
   for (int i = 0; i < h; i++)
   {
      std::string row;
      std::getline(std::cin, row);
      grid.push_back(row);
      std::cerr << row << std::endl;
      if (row.find(".") != std::string::npos || row.find("/") != std::string::npos || row.find("\\") != std::string::npos)
      {
         rectangle = false;
      }
   }

   if (rectangle)
   {
      std::cout << "Rectangle" << std::endl;
      return 0;
   }

   int first_column;
   int second_column;
   if (w % 2 == 0)
   {
      first_column = (w / 2) - 1;
      second_column = w / 2;
   }
   else
   {
      first_column = w / 2;
      second_column = first_column;
   }
   for (int i = 0; i < h; ++i)
   {
      if (grid[i][first_column] != 'X' || grid[i][second_column] != 'X')
      {
         std::cout << "Triangle" << std::endl;
         return 0;
      }
   }

   int first_row;
   int second_row;
   if (h % 2 == 0)
   {
      first_row = (h / 2) - 1;
      second_row = h / 2;
   }
   else
   {
      first_row = h / 2;
      second_row = first_row;
   }
   for (int j = 0; j < w; ++j)
   {
      if (grid[first_row][j] != 'X' || grid[second_row][j] != 'X')
      {
         std::cout << "Triangle" << std::endl;
         return 0;
      }
   }

   std::cout << "Ellipse" << std::endl;
}