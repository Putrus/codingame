#include <iostream>
#include <string>

int main()
{
   int surface_n; // the number of points used to draw the surface of Mars.
   std::cin >> surface_n; std::cin.ignore();
   for (int i = 0; i < surface_n; i++)
   {
      int land_x; // X coordinate of a surface point. (0 to 6999)
      int land_y; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
      std::cin >> land_x >> land_y; std::cin.ignore();
   }

   // game loop
   while (1)
   {
      int x;
      int y;
      int h_speed; // the horizontal speed (in m/s), can be negative.
      int v_speed; // the vertical speed (in m/s), can be negative.
      int fuel; // the quantity of remaining fuel in liters.
      int rotate; // the rotation angle in degrees (-90 to 90).
      int power; // the thrust power (0 to 4).
      std::cin >> x >> y >> h_speed >> v_speed >> fuel >> rotate >> power; std::cin.ignore();

      if (y > 1500)
      {
         std::cout << "0 3" << std::endl;
      }
      else if (y > 200)
      {
         std::cout << "0 4" << std::endl;
      }
      else
      {
         std::cout << "0 0" << std::endl;
      }
   }
}