#include <iostream>
#include <string>

constexpr int LANDING_THRESHOLD = 100;
constexpr int LANDING_HS_LIMIT = 10; //20 - 10
constexpr int LANDING_VS_LIMIT = 30; //40 - 10
constexpr int FLYING_HS_MAX = 45;

int main()
{
   int n;
   std::cin >> n; std::cin.ignore();
   int last_land_x = 0;
   int last_land_y = 0;
   int landing_x = 0;
   int landing_length = 0;
   for (int i = 0; i < n; i++)
   {
      int land_x; 
      int land_y;
      std::cin >> land_x >> land_y; std::cin.ignore();
      if (land_y == last_land_y)
      {
         landing_x = (land_x + last_land_x) / 2;
         landing_length = land_x - last_land_x;
      }
      last_land_y = land_y;
      last_land_x = land_x;
   }

   while (true) 
   {
      int x;
      int y;
      int hs; 
      int vs; 
      int f;
      int r;
      int p;
      std::cin >> x >> y >> hs >> vs >> f >> r >> p; std::cin.ignore();
      if (abs(landing_x - x) < (landing_length + LANDING_THRESHOLD) / 2)
      {
         if (hs > LANDING_HS_LIMIT)
         {
            std::cout << "50 4" << std::endl;
         }
         else if (hs < -LANDING_HS_LIMIT)
         {
            std::cout << "-50 4" << std::endl;
         }
         else
         {
            if (vs < -LANDING_VS_LIMIT)
            {
               std::cout << "0 4" << std::endl;
            }
            else
            {
               std::cout << "0 2" << std::endl;
            }
         }
      }
      else if (landing_x > x)
      {
         if (hs > FLYING_HS_MAX)
         {
            std::cout << "20 4" << std::endl;
         }
         else
         {
            std::cout << "-20 4" << std::endl;
         }
      }
      else
      {
         if (hs < -FLYING_HS_MAX)
         {
            std::cout << "-20 4" << std::endl;
         }
         else
         {
            std::cout << "20 4" << std::endl;
         }
      }
   }
}