#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

   bool x_found = false;
   // game loop
   int start = 0;
   int end = w - 1;
   while (1)
   {
      std::string bomb_dir; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
      std::cin >> bomb_dir; std::cin.ignore();
      std::cerr << bomb_dir << std::endl;
      //searching x direction
      if (!x_found)
      {
         if (bomb_dir == "WARMER")
         {
            start = x0 + 1;
         }
         else if (bomb_dir == "COLDER")
         {
            end = x0 - 1;
         }
         else if (bomb_dir == "SAME")
         {
            x_found = true;
            start = 0;
            end = h - 1;
         }

         if (!x_found)
         {
            x0 = (start + end) / 2;
         }
      }
      else
      {
         if (bomb_dir == "WARMER")
         {
            start = y0 + 1;
         }
         else if (bomb_dir == "COLDER")
         {
            end = y0 - 1;
         }
         y0 = (start + end) / 2;
      }

      std::cout << x0 << " " << y0 << std::endl;
   }
}