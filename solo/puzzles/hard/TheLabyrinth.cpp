#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <map>
#include <optional>

enum class Move : int
{
   Up = 0,
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
   Move last_move = Move::Right;
   std::unordered_set<Position> history;

   std::map<Move, std::vector<Move>> moves_priority =
      { { Move::Up, { Move::Up, Move::Left, Move::Right, Move::Down } },
      { Move::Down, { Move::Down, Move::Left, Move::Right, Move::Up } },
      { Move::Left, { Move::Left, Move::Up, Move::Down, Move::Right } },
      { Move::Right, { Move::Right, Move::Up, Move::Down, Move::Left } } };

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
            std::optional<Move> new_move;
            std::vector<Move> possible_moves;
            for (const auto& potential_next_move : moves_priority[last_move])
            {
               Position new_pos = { kc, kr, 0 };
               switch (potential_next_move)
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
            
               if ((maze[new_pos.y][new_pos.x] == '.' || maze[new_pos.y][new_pos.x] == 'T' || maze[new_pos.y][new_pos.x] == 'C'))
               {
                  possible_moves.push_back(potential_next_move);
                  if (history.find(Position{ kr, kc, static_cast<int>(potential_next_move) }) == history.end())
                  {
                     new_move = potential_next_move;
                     history.insert(Position{ kr, kc, static_cast<int>(last_move) });
                     break;
                  }  
               }
            }

            if (new_move)
            {
               last_move = new_move.value();
            }
            else if (!possible_moves.empty())
            {
               last_move = possible_moves[0];
            }
            else
            {
               std::cerr << "No possible moves" << std::endl;
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