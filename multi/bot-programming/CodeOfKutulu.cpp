#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Entity
{
   int x;
   int y;
};

int main()
{
   int width;
   std::cin >> width; std::cin.ignore();
   int height;
   std::cin >> height; std::cin.ignore();
   std::vector<std::string> level;
   for (int i = 0; i < height; i++)
   {
      std::string line;
      std::getline(std::cin, line);
      level.push_back(line);
   }
   int sanity_loss_lonely; // how much sanity you lose every turn when alone, always 3 until wood 1
   int sanity_loss_group; // how much sanity you lose every turn when near another player, always 1 until wood 1
   int wanderer_spawn_time; // how many turns the wanderer take to spawn, always 3 until wood 1
   int wanderer_life_time; // how many turns the wanderer is on map after spawning, always 40 until wood 1
   std::cin >> sanity_loss_lonely >> sanity_loss_group >> wanderer_spawn_time >> wanderer_life_time; std::cin.ignore();

   // game loop
   while (1)
   {
      int entity_count; // the first given entity corresponds to your explorer
      std::cin >> entity_count; std::cin.ignore();
      std::vector<Entity> wanderers;
      Entity player;
      for (int i = 0; i < entity_count; i++)
      {
         std::string entity_type;
         int id;
         int x;
         int y;
         int param_0;
         int param_1;
         int param_2;
         std::cin >> entity_type >> id >> x >> y >> param_0 >> param_1 >> param_2; std::cin.ignore();
         if (entity_type == "WANDERER")
         {
            wanderers.push_back({ x, y });
         }
         if (i == 0)
         {
            player = { x, y };
         }
      }

      bool wait = true;
      for (const auto& wanderer : wanderers)
      {
         if (std::abs(wanderer.x - player.x) == 2 && wanderer.y == player.y)
         {
            int change_x = -(wanderer.x - player.x) / std::abs(wanderer.x - player.x);
            int new_x = player.x + change_x;
            if (level[player.y][new_x] != '#')
            {
               std::cout << "MOVE " << new_x << " " << player.y << std::endl;
            }
            else if (level[player.y + 1][player.x] != '#')
            {
               std::cout << "MOVE " << player.x << " " << player.y + 1 << std::endl;
            }
            else if (level[player.y - 1][player.x] != '#')
            {
               std::cout << "MOVE " << player.x << " " << player.y - 1 << std::endl;
            }
            else
            {
               wait = true;
               break;
            }
            wait = false;
            break;
         }

         if (std::abs(wanderer.y - player.y) == 2 && wanderer.x == player.x)
         {
            int change_y = -(wanderer.y - player.y) / std::abs(wanderer.y - player.y);
            int new_y = player.y + change_y;
            if (level[new_y][player.x] != '#')
            {
               std::cout << "MOVE " << player.x << " " << new_y << std::endl;
            }
            else if (level[player.y][player.x + 1] != '#')
            {
               std::cout << "MOVE " << player.x + 1 << " " << player.y << std::endl;
            }
            else if (level[player.y][player.x - 1] != '#')
            {
               std::cout << "MOVE " << player.x - 1 << " " << player.y << std::endl;
            }
            else
            {
               wait = true;
               break;
            }
            wait = false;
            break;
         }
      }

      if (wait)
      {
         std::cout << "WAIT" << std::endl;
      }
   }
}