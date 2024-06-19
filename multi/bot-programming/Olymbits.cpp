#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

struct Race
{
   int player_position = 0;
   int player_stun = 0;
   std::string racetrack;

   int rateMove(const std::string& move) const
   {
      int score = 0;
      if (move == "UP")
      {
         if (player_position + 1 == racetrack.size())
         {
            return score;
         }
         score += 1;
         if (player_position + 2 == racetrack.size())
         {
            return score;
         }

         if (racetrack[player_position + 1] == '#')
         {
            score += 3;
         }

         if (racetrack[player_position + 2] == '#')
         {
            score -= 3;
         }
      }
      else if (move == "LEFT")
      {
         score += 1;
         if (player_position + 1 <= racetrack.size() && racetrack[player_position + 1] == '#')
         {
            score -= 3;
         }
      }
      else if (move == "DOWN")
      {
         for (int i = 1; i <= 2; ++i)
         {
            if (player_position + i == racetrack.size())
            {
               break;
            }
            
            ++score;
            
            if (racetrack[player_position + i] == '#')
            {
               score -= 3;
            }
         }
      }
      else
      {
         for (int i = 1; i <= 3; ++i)
         {
            if (player_position + i == racetrack.size())
            {
               break;
            }

            ++score;
            
            if (racetrack[player_position + i] == '#')
            {
               score -= 3;
            }
         }
      }

      return score;
   }
};

int rateMove(const std::vector<Race>& races, const std::string& move)
{
   int score = 0;
   for (const auto& race : races)
   {
      if (race.player_stun > 0)
      {
         continue;
      }
      
      score += race.rateMove(move);
   }
   return score;
}

int main()
{
   int player_idx;
   std::cin >> player_idx; std::cin.ignore();
   int nb_games;
   std::cin >> nb_games; std::cin.ignore();
   int player_position = 0;
   std::vector<Race> races(4);
   // game loop
   while (1)
   {
      std::map<int, int> distances_to_hurdles;
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

         if (player_idx == 0)
         {
            races[i].player_position = reg_0;
            races[i].player_stun = reg_3;
            races[i].racetrack = gpu;
         }

         if (player_idx == 1)
         {
            races[i].player_position = reg_1;
            races[i].player_stun = reg_4;
            races[i].racetrack = gpu;
         }

         if (player_idx == 2)
         {
            races[i].player_position = reg_2;
            races[i].player_stun = reg_5;
            races[i].racetrack = gpu;
         }
      }

      int best_score = -999;
      std::string best_move = "UNKNOWN";

      int up_score = rateMove(races, "UP");
      std::cerr << "UP: " << up_score << std::endl;
      if (up_score > best_score)
      {
         best_score = up_score;
         best_move = "UP";
      }
      
      int left_score = rateMove(races, "LEFT");
      std::cerr << "LEFT: " << left_score << std::endl;
      if (left_score > best_score)
      {
         best_score = left_score;
         best_move = "LEFT";
      }

      int down_score = rateMove(races, "DOWN");
      std::cerr << "DOWN: " << down_score << std::endl;
      if (down_score > best_score)
      {
         best_score = down_score;
         best_move = "DOWN";
      }

      int right_score = rateMove(races, "RIGHT");
      std::cerr << "RIGHT: " << right_score << std::endl;
      if (right_score > best_score)
      {
         best_score = right_score;
         best_move = "RIGHT";
      }

      std::cout << best_move << std::endl;
   }
}