#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <stack>
#include <unordered_set>

constexpr int MAX_BOARD_SIZE = 11;

struct Position
{
   int x = 0;
   int y = 0;
};

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

struct Bitboard
{
   long long a = 0;
   long long b = 0;

   long long getIndex(int x, int y) const
   {
      return y * MAX_BOARD_SIZE + x;
   }

   bool getBit(int x, int y) const
   {
      long long index = getIndex(x, y);
      if (index < 64LL)
      {
         return b & (1LL << index);
      }
      else
      {
         return a & (1LL << (index - 64));
      }
   }

   bool getBit(const Position& position) const
   {
      return getBit(position.x, position.y);
   }

   void setBit(int x, int y, bool value = 1)
   {
      long long index = getIndex(x, y);
      if (index < 64LL)
      {
         if (value)
         {
            b |= 1LL << index;
         }
         else
         {
            b &= ~(1LL << index);
         }
      }
      else
      {
         if (value)
         {
            a |= 1LL << (index - 64);
         }
         else
         {
            a &= ~(1LL << (index - 64));
         }
         
      }
   }

   void setBit(const Position& position, bool value = 1)
   {
      setBit(position.x, position.y, value);
   }
};

std::ostream& operator<<(std::ostream& os, const Bitboard& bitboard)
{
    std::bitset<57> a_bits(bitboard.a);
    std::bitset<64> b_bits(bitboard.b);

    os << a_bits << " " <<  b_bits;
    return os;
}

bool operator==(const Bitboard& lhs, const Bitboard& rhs)
{
   return lhs.a == rhs.a && lhs.b == rhs.b;
}

struct State
{
   Position pusher;
   Bitboard boxes;
};

bool operator==(const State& lhs, const State& rhs)
{
   return lhs.pusher == rhs.pusher && lhs.boxes == rhs.boxes;
}

namespace std
{
   template <>
   struct hash<State>
   {
      size_t operator()(const State& state) const noexcept
      {
         size_t hash_value = 17;
         hash_value = hash_value * 31 + std::hash<int>{}(state.pusher.x);
         hash_value = hash_value * 31 + std::hash<int>{}(state.pusher.y);
         hash_value = hash_value * 31 + std::hash<long long>{}(state.boxes.a);
         hash_value = hash_value * 31 + std::hash<long long>{}(state.boxes.b);
         return hash_value;
      }
   };
}

Position getMoveDirection(char move)
{
   switch (move)
   {
   case 'U':
      return { 0, -1 };
   case 'L':
      return { -1, 0 };
   case 'D':
      return { 0, 1 };
   case 'R':
      return { 1, 0 };
   }
   return { 0, 0 };
}

enum class Move
{
   Impossible = 0,
   Push,
   Run
};

Move move(char move, State& state, const Bitboard& walls, const Bitboard& win)
{
   Position direction = getMoveDirection(move);

   Position pusher_new_pos = state.pusher + direction;

   if (!walls.getBit(pusher_new_pos))
   {
      if (state.boxes.getBit(pusher_new_pos))
      {
         Position potential_box_new_pos = pusher_new_pos + direction;
         if (walls.getBit(potential_box_new_pos) || state.boxes.getBit(potential_box_new_pos) ||
            (!win.getBit(potential_box_new_pos) &&
            ((walls.getBit(potential_box_new_pos.x + 1, potential_box_new_pos.y) || walls.getBit(potential_box_new_pos.x - 1, potential_box_new_pos.y)) &&
            (walls.getBit(potential_box_new_pos.x, potential_box_new_pos.y + 1) || walls.getBit(potential_box_new_pos.x, potential_box_new_pos.y - 1)))))
         {
            return Move::Impossible;
         }
         state.boxes.setBit(pusher_new_pos, 0);
         state.boxes.setBit(potential_box_new_pos);
         state.pusher = pusher_new_pos;
         return Move::Push;
      }

      state.pusher = pusher_new_pos;
      return Move::Run;
   }
   else
   {
      return Move::Impossible;
   }
}

int main()
{
   int width;
   int height;
   int box_count;
   std::cin >> width >> height >> box_count; std::cin.ignore();
   Bitboard wall_bitboard;
   Bitboard win_bitboard;
   Bitboard boxes;
   for (int i = 0; i < height; ++i)
   {
      std::string line;
      std::getline(std::cin, line);
      for (int j = 0; j < line.size(); ++j)
      {
         if (line[j] == '#')
         {
            wall_bitboard.setBit(j, i);
         }
         if (line[j] == '*' )
         {
            win_bitboard.setBit(j, i);
         }
      }
   }
   // game loop
   int turn = 0;
   std::string moves;
   State state_copy;
   Move ret = Move::Impossible;
   while (1)
   {
      Position pusher;
      std::cin >> pusher; std::cin.ignore();
      for (int i = 0; i < box_count; i++)
      {
         Position box;
         std::cin >> box; std::cin.ignore();
         boxes.setBit(box);
      }

      if (turn == 0)
      {
         std::deque<std::pair<State, std::string>> states;
         states.push_back({ { pusher, boxes }, "" });
         std::unordered_set<State> history;
         while (!states.empty())
         {
            auto current_state = states.front();
            states.pop_front();

            if (current_state.first.boxes == win_bitboard)
            {
               moves = std::move(current_state.second);
               break;
            }

            if (history.find(current_state.first) != history.end())
            {
               continue;
            }

            history.insert(current_state.first);

            if (current_state.second.size() >= 400)
            {
               continue;
            }

            state_copy = current_state.first;
            for (char next_move : "ULRD")
            {
               ret = move(next_move, state_copy, wall_bitboard, win_bitboard);
               if (ret != Move::Impossible)
               {
                  if (ret == Move::Push)
                  {
                     states.push_front({ state_copy, current_state.second + next_move });
                  }
                  else
                  {
                     states.push_back({ state_copy, current_state.second + next_move });
                  }
                  state_copy = current_state.first;
               }
            }            
         }
      }

      std::cerr << moves.size() << std::endl;
      std::cout << moves[turn] << std::endl;
      ++turn;
   }
}