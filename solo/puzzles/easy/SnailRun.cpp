#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

struct Point
{
   int x;
   int y;
};

std::ostream& operator<<(std::ostream& os, const Point& point)
{
   os << point.x << ' ' << point.y;
   return os;
}

struct Snail
{
   int speed;
   Point position;
   Point goal;

   void findPosition(int id, const std::vector<std::string>& map);
   void findGoal(const std::vector<std::string>& map);

   bool update(const std::vector<std::string>& map);
};

void Snail::findPosition(int id, const std::vector<std::string>& map)
{
   for (int i = 0; i < map.size(); ++i)
   {
      for (int j = 0; j < map[i].size(); ++j)
      {
         if (map[i][j] - '0' == id + 1)
         {
            position.x = j;
            position.y = i;
            return;
         }
      }
   }
}

void Snail::findGoal(const std::vector<std::string> &map)
{
   double best_distance = std::numeric_limits<double>::max();
   for (int i = 0; i < map.size(); ++i)
   {
      for (int j = 0; j < map[i].size(); ++j)
      {
         if (map[i][j] == '#')
         {
            double distance = std::sqrt((i - position.y) * (i - position.y) + (j - position.x) * (j - position.x));
            if (distance < best_distance)
            {
               best_distance = distance;
               goal = { j, i };
            }
         }
      }
   } 
}

bool Snail::update(const std::vector<std::string> &map)
{
   for (int i = 0; i < speed; ++i)
   {
      if (position.x < goal.x)
      {
         ++position.x;
      }
      else if (position.x > goal.x)
      {
         --position.x;
      }
      else if (position.y < goal.y)
      {
         ++position.y;
      }
      else if (position.y > goal.y)
      {
         --position.y;
      }

      if (position.x == goal.x && position.y == goal.y)
      {
         return true;
      }
   }

   return false;
}

int main()
{
   int number_snails;
   std::cin >> number_snails; std::cin.ignore();
   std::vector<Snail> snails(number_snails);
   for (int i = 0; i < number_snails; i++)
   {
      int speed_snail;
      std::cin >> speed_snail; std::cin.ignore();
      snails[i].speed = speed_snail;
   }
   int map_height;
   std::cin >> map_height; std::cin.ignore();
   int map_width;
   std::cin >> map_width; std::cin.ignore();
   std::vector<std::string> map;
   for (int i = 0; i < map_height; i++)
   {
      std::string row;
      std::getline(std::cin, row);
      map.push_back(row);
   }

   for (int id = 0; id < snails.size(); ++id)
   {
      snails[id].findPosition(id, map);
      snails[id].findGoal(map);
   }

   int turn = 0;
   while (true)
   {
      std::cerr << "Turn " << turn << std::endl;
      for (int id = 0; id < snails.size(); ++id)
      {
         if (snails[id].update(map))
         {
            std::cout << id + 1 << std::endl;
            return 0;
         }
      }
      ++turn;
   }
}