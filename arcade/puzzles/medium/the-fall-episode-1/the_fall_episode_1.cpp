#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main()
{
   int w; // number of columns.
   int h; // number of rows.
   std::cin >> w >> h; std::cin.ignore();
   std::vector<std::vector<int>> tunnel;
   for (int i = 0; i < h; i++)
   {
      std::string line;
      std::getline(std::cin, line); // represents a line in the grid and contains W integers. Each integer represents one room of a given type.
      std::stringstream ss(line);
      std::vector<int> row;
      while (!ss.eof())
      {
         int type;
         ss >> type;
         row.push_back(type);
      }
      tunnel.push_back(row);
   }
   int ex; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read).
   std::cin >> ex; std::cin.ignore();

   // game loop
   while (1)
   {
      int xi;
      int yi;
      std::string pos;
      std::cin >> xi >> yi >> pos; std::cin.ignore();

      if (pos == "TOP")
      {
         if (tunnel[yi][xi] == 1 || tunnel[yi][xi] == 3 || tunnel[yi][xi] == 7 || tunnel[yi][xi] == 9)
         {
            std::cout << xi << " " << yi + 1 << std::endl;
            continue;
         }
         else if (tunnel[yi][xi] == 4 || tunnel[yi][xi] == 10)
         {
            std::cout << xi - 1 << " " << yi << std::endl;
            continue;
         }
         else if (tunnel[yi][xi] == 5 || tunnel[yi][xi] == 11)
         {
            std::cout << xi + 1 << " " << yi << std::endl;
            continue;
         }
         else
         {
            std::cerr << "Impossible move " << tunnel[yi][xi] << std::endl;
         }
      }
      else if (pos == "LEFT")
      {
         if (tunnel[yi][xi] == 1 || tunnel[yi][xi] == 5 || tunnel[yi][xi] == 8 || tunnel[yi][xi] == 9 || tunnel[yi][xi] == 13)
         {
            std::cout << xi << " " << yi + 1 << std::endl;
            continue;
         }
         else if (tunnel[yi][xi] == 2 || tunnel[yi][xi] == 6)
         {
            std::cout << xi + 1 << " " << yi << std::endl;
            continue;
         }
         else
         {
            std::cerr << "Impossible move " << tunnel[yi][xi] << std::endl;
         }
      }
      else // right
      {
         if (tunnel[yi][xi] == 1 || tunnel[yi][xi] == 4 || tunnel[yi][xi] == 7 || tunnel[yi][xi] == 8 || tunnel[yi][xi] == 12)
         {
            std::cout << xi << " " << yi + 1 << std::endl;
            continue;
         }
         else if (tunnel[yi][xi] == 2 || tunnel[yi][xi] == 6)
         {
            std::cout << xi - 1 << " " << yi << std::endl;
            continue;
         }
         else
         {
            std::cerr << "Impossible move " << tunnel[yi][xi] << std::endl;
         }
      }

      std::cout << xi << " " << yi << std::endl;
   }
}