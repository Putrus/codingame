#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

struct Point
{
   int x;
   int y;
};

struct Human : public Point
{
   int id;
};

struct Zombie : public Human
{
   Point next;
};

int distance(const Point& a, const Point& b)
{
   return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

int main()
{
   while (1) {
      int x;
      int y;
      std::cin >> x >> y; std::cin.ignore();
      Point ash = { x, y };
      int human_count;
      std::cin >> human_count; std::cin.ignore();
      std::vector<Human> humans;
      std::vector<Zombie> zombies;
      for (int i = 0; i < human_count; i++) 
      {
         Human human;
         std::cin >> human.id >> human.x >> human.y; std::cin.ignore();
         humans.push_back(human);
      }
      int zombie_count;
      std::cin >> zombie_count; std::cin.ignore();
      for (int i = 0; i < zombie_count; i++)
      {
         Zombie zombie;
         std::cin >> zombie.id >> zombie.x >> zombie.y >> zombie.next.x >> zombie.next.y; std::cin.ignore();
         zombies.push_back(zombie);
      }

      std::vector<Human> saveable_humans;
      for (const auto& human : humans)
      {
         bool can_save = true;
         int turns_ash = (distance(ash, human) - 2000) / 1000;
         if (turns_ash < 0)
         {
            turns_ash = 0;
         }

         for (const auto& zombie : zombies)
         {
            int turns_zombie = distance(human, zombie) / 400;
            if (turns_zombie < turns_ash)
            {
               can_save = false;
               break;
            }
         }

         if (can_save)
         {
            saveable_humans.push_back(human);
         }
      }

      const auto& target_humans = saveable_humans.empty() ? humans : saveable_humans;

      Point destination = { 0, 0 };
      int best = std::numeric_limits<int>::max();
      for (const auto& zombie : zombies)
      {
         for (const auto& human : target_humans)
         {
            int dist = distance(human, zombie);
            if (dist < best)
            {
               best = dist;
               destination = zombie.next;
            }
         }
      }

      std::cout << destination.x << " " << destination.y << std::endl; // Your destination coordinates
   }
}
