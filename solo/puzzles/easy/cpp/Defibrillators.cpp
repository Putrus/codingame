#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

struct Defibrillator
{
   std::string name;
   float lon;
   float lat;
};

int main()
{
   std::string lon;
   std::cin >> lon; std::cin.ignore();
   std::string lat;
   std::cin >> lat; std::cin.ignore();
   int n;
   std::cin >> n; std::cin.ignore();
   std::vector<Defibrillator> defibrillators;
   
   std::replace(lon.begin(), lon.end(), ',', '.');
   std::replace(lat.begin(), lat.end(), ',', '.');
   float longitude = std::stof(lon);
   float latitude = std::stof(lat);
   for (int i = 0; i < n; i++)
   {
      std::string defib;
      std::getline(std::cin, defib);
      std::stringstream ss(defib);
      int j = 0;
      std::string attr;
      Defibrillator d;
      while (std::getline(ss, attr, ';'))
      {
         if (j == 1)
         {
            d.name = attr;
         }
         else if (j == 4)
         {
            std::replace(attr.begin(), attr.end(), ',', '.');
            d.lon = std::stof(attr);
         }
         else if (j == 5)
         {
            std::replace(attr.begin(), attr.end(), ',', '.');
            d.lat = std::stof(attr);
         }
         ++j;
      }
      defibrillators.push_back(d);
   }

   float best = std::numeric_limits<float>::max();
   std::string best_name;
   for (const auto& defibrillator : defibrillators)
   {
      float x = (defibrillator.lon - longitude) * std::cos((defibrillator.lat + latitude) / 2.f);
      float y = (defibrillator.lat - latitude);
      float dist = std::sqrt(x * x + y * y) * 6371.f;
      if (dist < best)
      {
         best = dist;
         best_name = defibrillator.name;
      }
   }

   std::cout << best_name << std::endl;
}