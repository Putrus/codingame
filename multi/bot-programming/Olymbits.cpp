#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

int main()
{
   int player_idx;
   std::cin >> player_idx; std::cin.ignore();
   int nb_games;
   std::cin >> nb_games; std::cin.ignore();
   int player_position = 0;
   std::string racetrack;
   // game loop
   while (1)
   {
      std::map<int, int> distances_to_hurdles;
      for (int i = 0; i < 3; i++)
      {
         std::string score_info;
         getline(std::cin, score_info);
      }
      std::cerr << "nb_games = " << nb_games << std::endl;
      for (int i = 0; i < nb_games; i++)
      {
         std::string gpu;
         int reg_0;
         int reg_1;
         int reg_2;
         int reg_3;
         int reg_4;
         int reg_5;
         int reg_6;
         std::cin >> gpu >> reg_0 >> reg_1 >> reg_2 >> reg_3 >> reg_4 >> reg_5 >> reg_6; std::cin.ignore();

         racetrack = gpu;
         if (player_idx == 0 && reg_3 != 0)
         {
            continue;
         }

         if (player_idx == 1 && reg_4 != 0)
         {
            continue;
         }

         if (player_idx == 2 && reg_5 != 0)
         {
            continue;
         }
         
         int dist = 1;
         for (int j = player_position + 1; j < racetrack.size(); ++j)
         {
            if (racetrack[j] == '#')
            {
               break;
            }
            ++dist;
         }

         if (dist >= 4)
         {
            if (distances_to_hurdles.find(4) == distances_to_hurdles.end())
            {
               distances_to_hurdles.insert({ 4, 1 });
            }
            else
            {
               ++distances_to_hurdles[4];
            }
         }
         else
         {
            if (distances_to_hurdles.find(dist) == distances_to_hurdles.end())
            {
               distances_to_hurdles.insert({ dist, 1 });
            }
            else
            {
               ++distances_to_hurdles[dist];
            }
            
         }
      }

      std::pair<int, int> best = { 0, 0 };

      std::cerr << distances_to_hurdles.size() << std::endl;
      for (const auto& d : distances_to_hurdles)
      {
         std::cerr << d.first << " " << d.second << std::endl;
         if (d.second >= best.second)
         {
            best = d;
         }
      }

      if (best.first == 1)
      {
         std::cout << "UP" << std::endl;
      }
      else if (best.first == 2)
      {
         std::cout << "LEFT" << std::endl;
      }
      else if (best.first == 3)
      {
         std::cout << "DOWN" << std::endl;
      }
      else
      {
         std::cout << "RIGHT" << std::endl;
      }
   }
}