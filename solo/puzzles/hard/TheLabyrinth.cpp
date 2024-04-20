#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

enum class Move : int
{
   Start = 0,
   Up,
   Down,
   Left,
   Right
};

std::ostream& operator<<(std::ostream& os, const Move& move)
{
   switch (move)
   {
      case Move::Start:
      {
         os << "START";
         break;
      }
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
   int move = 0;
};

std::ostream& operator<<(std::ostream& os, const Position& position)
{
   os << position.x << ' ' << position.y << ' ' << static_cast<Move>(position.move);
   return os;
}

std::istream& operator>>(std::istream& is, Position& position)
{
   is >> position.x >> position.y;
   return is;
}

bool operator==(const Position& lhs, const Position& rhs)
{
   return lhs.x == rhs.x && lhs.y == rhs.y && lhs.move == rhs.move;
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
         hash_value = hash_value * 31 + std::hash<long long>{}(position.move);
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
   Move last_move = Move::Start;
   std::unordered_set<Position> history;

   // game loop
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
         std::cerr << row << std::endl;
         for (int j = 0; j < row.size(); ++j)
         {
            if (row[j] == 'C')
            {
               std::cerr << "Find C in " << i << " " << j << std::endl;
               //phase = Phase::GoToC;
            }
         }
      }
      std::cerr << "Position: " << kr << " " << kc << std::endl;
      std::cerr << "History: " << std::endl;
      for (const auto& pos : history)
      {
         std::cerr << pos << std::endl; 
      }

      switch (phase)
      {
         case Phase::LookingForC:
         {
            if ((maze[kr][kc + 1] == '.' || maze[kr][kc + 1] == 'T' || maze[kr][kc + 1] == 'C') &&
               history.find(Position{ kr, kc, static_cast<int>(Move::Right) }) == history.end())
            {
               last_move = Move::Right;
               history.insert(Position{ kr, kc, static_cast<int>(last_move) });
            }
            else if ((maze[kr][kc - 1] == '.' || maze[kr][kc - 1] == 'T' || maze[kr][kc - 1] == 'C') &&
               history.find(Position{ kr, kc, static_cast<int>(Move::Left) }) == history.end())
            {
               last_move = Move::Left;
               history.insert(Position{ kr, kc, static_cast<int>(last_move) });
            }
            else if ((maze[kr + 1][kc] == '.' || maze[kr + 1][kc] == 'T' || maze[kr + 1][kc] == 'C') &&
               history.find(Position{ kr, kc, static_cast<int>(Move::Down) }) == history.end())
            {
               last_move = Move::Down;
               history.insert(Position{ kr, kc, static_cast<int>(last_move) });
            }
            else if ((maze[kr - 1][kc] == '.' || maze[kr - 1][kc] == 'T' || maze[kr - 1][kc] == 'C') &&
               history.find(Position{ kr, kc, static_cast<int>(Move::Up) }) == history.end())
            {
               last_move = Move::Up;
               history.insert(Position{ kr, kc, static_cast<int>(last_move) });
            }
            else
            {
               std::cerr << "What the fuck?" << std::endl;
            }
            
            std::cout << last_move << std::endl;
            break;
         }
         case Phase::GoToC:
         {
            break;
         }
         case Phase::GoToT:
         {
            break;
         }
         default:
         {
            std::cerr << "Wrong phase" << std::endl;
            break;
         }
      }
   }
}