#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
      for (int i = 0; i < 3; i++)
      {
         std::string score_info;
         getline(std::cin, score_info);
      }
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

         if (player_idx == 0)
         {
            player_position = reg_0;
         }
         else if (player_idx == 1)
         {
            player_position = reg_1;
         }
         else
         {
            player_position = reg_2;
         }
      }

      if (player_position + 1 < racetrack.size() && racetrack[player_position + 1] == '#')
      {
         std::cout << "UP" << std::endl;
      }
      else if (player_position + 2 < racetrack.size() && racetrack[player_position + 2] == '#')
      {
         std::cout << "LEFT" << std::endl;
      }
      else if (player_position + 3 < racetrack.size() && racetrack[player_position + 3] == '#')
      {
         std::cout << "DOWN" << std::endl;
      }
      else
      {
         std::cout << "RIGHT" << std::endl;
      }
   }
}