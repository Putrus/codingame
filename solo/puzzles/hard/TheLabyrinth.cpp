#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <deque>

enum class Move : int
{
   Start = 0,
   Up,
   Down,
   Left,
   Right
};

bool operator<(Move lhs, Move rhs)
{
   return static_cast<int>(lhs) < static_cast<int>(rhs);
}

std::ostream& operator<<(std::ostream& os, const Move& move)
{
   switch (move)
   {
      case Move::Up:
      {
         os << "UP";
         break;
      }
      case Move::Down:
      {
         os << "DOWN";
         break;
      }
      case Move::Left:
      {
         os << "LEFT";
         break;
      }
      case Move::Right:
      {
         os << "RIGHT";
         break;
      }
      default:
      {
         os << "WRONG";
         break;
      }
   }
   return os;
}

struct Position
{
   int x = 0;
   int y = 0;
};

std::ostream& operator<<(std::ostream& os, const Position& position)
{
   os << position.x << ' ' << position.y;
   return os;
}

std::istream& operator>>(std::istream& is, Position& position)
{
   is >> position.x >> position.y;
   return is;
}

bool operator==(const Position& lhs, const Position& rhs)
{
   return lhs.x == rhs.x && lhs.y == rhs.y;
}

Position operator+(const Position& lhs, const Position& rhs)
{
   return { lhs.x + rhs.x, lhs.y + rhs.y };
}

namespace std
{
   template <>
   struct hash<Position>
   {
      size_t operator()(const Position& position) const noexcept
      {
         size_t hash_value = 17;
         hash_value = hash_value * 31 + std::hash<int>{}(position.x);
         hash_value = hash_value * 31 + std::hash<int>{}(position.y);
         return hash_value;
      }
   };
}

enum class Phase
{
   LookingForC,
   GoToC,
   GoToT
};

int main()
{
   int r; // number of rows.
   int c; // number of columns.
   int a; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
   std::cin >> r >> c >> a; std::cin.ignore();

   Phase phase = Phase::LookingForC;
   // game loop
   char wanted = '?';
   while (1)
   {
      int kr; // row where Rick is located.
      int kc; // column where Rick is located.
      std::cin >> kr >> kc; std::cin.ignore();
      std::vector<std::string> maze;
      for (int i = 0; i < r; i++)
      {
         std::string row; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
         std::cin >> row; std::cin.ignore();
         maze.push_back(row);
      }

      if (maze[kr][kc] == 'C')
      {
         wanted = 'T';
      }

      Move move = Move::Start;
      while (move == Move::Start)
      {
         std::unordered_set<Position> history;
         std::deque<std::pair<Position, Move>> que;
         que.push_back({ { kc, kr }, Move::Start });
         std::cerr << "Wanted = " << wanted << std::endl;
         while (!que.empty())
         {
            auto current_pos = que.front();
            que.pop_front();

            history.insert(current_pos.first);

            if (maze[current_pos.first.y][current_pos.first.x] == wanted)
            {
               move = current_pos.second;
               break;
            }

            for (Move next_move : { Move::Up, Move::Down, Move::Left, Move::Right })
            {
               Position new_pos = current_pos.first;
               switch (next_move)
               {
                  case Move::Up:
                  {
                     --new_pos.y;
                     break;
                  }
                  case Move::Down:
                  {
                     ++new_pos.y;
                     break;
                  }
                  case Move::Right:
                  {
                     ++new_pos.x;
                     break;
                  }
                  case Move::Left:
                  {
                     --new_pos.x;
                     break;
                  }
                  default:
                  {
                     std::cerr << "Wrong move" << std::endl;
                     break;
                  }
               }
               if (new_pos.y >= 0 && new_pos.y < maze.size() && new_pos.x >= 0 && new_pos.x < maze[new_pos.y].size() &&
                  maze[new_pos.y][new_pos.x] != '#' &&
                  history.find(new_pos) == history.end())
               {
                  if (current_pos.second == Move::Start)
                  {
                     que.push_back({ new_pos, next_move });
                  }
                  else
                  {
                     que.push_back({ new_pos, current_pos.second });
                  }
               }
            }
         }

         if (wanted == '?' && move == Move::Start)
         {
            wanted = 'C';
         }
      }
      
      std::cout << move << std::endl;
   }
}