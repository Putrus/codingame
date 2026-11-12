#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Player
{
public:
   void addOpponent(int num)
   {
      opponents.push_back(num);
   }

   int getNum() const
   {
      return num;
   }

   char getSign() const
   {
      return sign;
   }

   friend std::istream& operator>>(std::istream& is, Player& player);
   friend std::ostream& operator<<(std::ostream& os, const Player& player);
private:
   int num;
   char sign;
   std::vector<int> opponents;
};

std::istream& operator>>(std::istream& is, Player& player)
{
   is >> player.num >> player.sign;
   return is;
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
   os << player.num << std::endl;
   if (player.opponents.empty())
      return os;
   for (int i = 0; i < player.opponents.size() - 1; ++i)
   {
      os << player.opponents[i] << ' ';
   }
   os << player.opponents.back();
   return os;
}

int main()
{
   int n;
   std::cin >> n; std::cin.ignore();
   std::vector<Player> players;
   for (int i = 0; i < n; i++)
   {
      Player player;
      std::cin >> player; std::cin.ignore();
      players.push_back(player);
   }

   int round = 0;
   while (players.size() > 1)
   {
      std::vector<Player> winners;
      for (int i = 0; i < players.size(); i += 2)
      {
         char sign1 = players[i].getSign();
         char sign2 = players[i + 1].getSign();

         if ((sign1 == 'C' && sign2 == 'P') ||
            (sign1 == 'P' && sign2 == 'R') ||
            (sign1 == 'R' && sign2 == 'L') ||
            (sign1 == 'L' && sign2 == 'S') ||
            (sign1 == 'S' && sign2 == 'C') ||
            (sign1 == 'C' && sign2 == 'L') ||
            (sign1 == 'L' && sign2 == 'P') ||
            (sign1 == 'P' && sign2 == 'S') ||
            (sign1 == 'S' && sign2 == 'R') ||
            (sign1 == 'R' && sign2 == 'C') ||
            (sign1 == sign2 && players[i].getNum() <= players[i + 1].getNum()))
         {
            Player winner = players[i];
            winner.addOpponent(players[i + 1].getNum());
            winners.push_back(winner);
         }
         else
         {
            Player winner = players[i + 1];
            winner.addOpponent(players[i].getNum());
            winners.push_back(winner);
         }
      }
      players = std::move(winners);
   }
   std::cout << players.back() << std::endl;
}
