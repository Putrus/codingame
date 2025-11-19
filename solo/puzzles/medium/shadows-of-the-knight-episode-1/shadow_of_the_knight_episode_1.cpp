#include <iostream>
#include <string>
#include <vector>

struct Rect
{
   int left;
   int top;
   int right;
   int bottom;
};

int main()
{
   int w; // width of the building.
   int h; // height of the building.
   std::cin >> w >> h; std::cin.ignore();
   int n; // maximum number of turns before game over.
   std::cin >> n; std::cin.ignore();
   int x0;
   int y0;
   std::cin >> x0 >> y0; std::cin.ignore();
   Rect building = {0, 0, w - 1, h - 1};
   // game loop
   while (1)
   {
      std::string bomb_dir;
      std::cin >> bomb_dir; std::cin.ignore();
      if (bomb_dir.find('U') != std::string::npos)
      {
         building.bottom = y0 - 1;
      }
      else if (bomb_dir.find('D') != std::string::npos)
      {
         building.top = y0 + 1;
      }

      if (bomb_dir.find('L') != std::string::npos)
      {
         building.right = x0 - 1;
      }
      else if (bomb_dir.find('R') != std::string::npos)
      {
         building.left = x0 + 1;
      }
      y0 = (building.top + building.bottom) / 2;
      x0 = (building.left + building.right) / 2;
      std::cout << x0 << " " << y0 << std::endl;
   }
}