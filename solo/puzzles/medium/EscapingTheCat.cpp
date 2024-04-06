#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

constexpr int POOL_RADIUS = 500;
constexpr int MOUSE_SPEED = 10;

int distance(int a_x, int a_y, int b_x, int b_y)
{
    return std::sqrt(static_cast<double>((b_x - a_x) * (b_x - a_x) + (b_y - a_y) * (b_y - a_y)));
}

int main()
{
   int cat_speed;
   std::cin >> cat_speed; std::cin.ignore();

   int small_radius = 13; 

   int destination_x = small_radius;
   int destination_y = 0;

   double angle = 0.0;
   double turns = (2 * M_PI * small_radius / (double)MOUSE_SPEED);
   double angle_increment = 2 * M_PI / turns;
   bool dash = false;
   int best = 0;
   // game loop
   while (1) {
      int mouse_x;
      int mouse_y;
      int cat_x;
      int cat_y;
      std::cin >> mouse_x >> mouse_y >> cat_x >> cat_y; std::cin.ignore();

      if (!dash)
      {
      if (mouse_x == destination_x || mouse_y == destination_y)
      {
         if (distance(mouse_x, mouse_y, cat_x, cat_y) >= 622 && small_radius >= 103)
         {
               angle += 5 * angle_increment;
               destination_x = (POOL_RADIUS + 100) * std::cos(angle);
               destination_y = (POOL_RADIUS + 100) * std::sin(angle);
               dash = true;
         }
         else
         {
               int old_destination_x = destination_x;
               int old_destination_y = destination_y;
               while (old_destination_x == destination_x || old_destination_y == destination_y)
               {
                  if (distance(mouse_x, mouse_y, cat_x, cat_y) >= POOL_RADIUS + small_radius - 5)
                  {
                     small_radius += 10;
                     turns = (2 * M_PI * small_radius / (double)MOUSE_SPEED);
                     angle_increment = 2 * M_PI / turns;
                  }
                  angle += angle_increment;
                  destination_x = small_radius * std::cos(angle);
                  destination_y = small_radius * std::sin(angle);
               }
         }
      }
      }
      int dist = distance(mouse_x, mouse_y, cat_x, cat_y);
      best = std::max(best, dist);
      std::cout << destination_x << " " << destination_y << " dist: " << dist << " best: " << best << std::endl;
   }
}