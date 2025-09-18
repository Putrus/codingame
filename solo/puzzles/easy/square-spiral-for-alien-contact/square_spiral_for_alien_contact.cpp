#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

struct Vec2
{
   int x;
   int y;
};

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& grid)
{
   int size = std::min(31, static_cast<int>(grid.size()));
   for (int i = 0; i < size; ++i)
   {
      for (int j = 0; j < size; ++j)
      {
         os << grid[i][j];
      }
      if (i < size - 1)
      {
         os << std::endl;
      }
   }
   return os;
}

int main()
{
   std::string cryptic_instructions;
   std::getline(std::cin, cryptic_instructions);
   std::stringstream ss(cryptic_instructions);
   int side_size;
   std::string start_pos, direction, pattern_first, pattern_second;
   ss >> side_size >> start_pos >> direction >> pattern_first >> pattern_second;

   std::vector<std::string> grid(side_size, std::string(side_size, ' '));
   
   Vec2 pos = { 0, 0 };
   Vec2 dir = { 0, 0 };
   if (start_pos == "topRight")
   {
      pos = { side_size - 1, 0 };
      if (direction == "clockwise")
      {
         dir.y = 1;
      }
      else
      {
         dir.x = -1;
      }
   }
   else if (start_pos == "topLeft")
   {
      pos = { 0, 0 };
      if (direction == "clockwise")
      {
         dir.x = 1;
      }
      else
      {
         dir.y = 1;
      }
   }
   else if (start_pos == "bottomRight")
   {
      pos = { side_size - 1, side_size - 1 };
      if (direction == "clockwise")
      {
         dir.x = -1;
      }
      else
      {
         dir.y = -1;
      }
   }
   else if (start_pos == "bottomLeft")
   {
      pos = { 0, side_size - 1 };
      if (direction == "clockwise")
      {
         dir.y = -1;
      }
      else
      {
         dir.x = 1;
      }
   }
   else
   {
      std::cerr << "Wrong start position: " << start_pos << std::endl;
      return -1;
   }
   if (pattern_first.length() < 2)
   {
      std::cerr << "First pattern length is less than 2!" << std::endl;
      return -1;
   }

   if (pattern_second.length() < 2)
   {
      std::cerr << "Second pattern length is less than 2!" << std::endl;
      return -1;
   }
   char first_char = pattern_first.at(0);
   char second_char = pattern_second.at(0);
   int char_diff = static_cast<int>(first_char - second_char);

   int first_size = std::stoi(pattern_first.substr(1));
   int second_size = std::stoi(pattern_second.substr(1));
   int size_diff = first_size - second_size;
   int size = first_size;
   char sign = first_char;
   int in_a_row = 0;
   int counter = 0;
   while (true)
   {
      for (int i = 0; i < size; ++i)
      {
         grid[pos.y][pos.x] = sign;
         ++in_a_row;
         Vec2 next_pos = pos;
         next_pos.x += dir.x;
         next_pos.y += dir.y;
         Vec2 next_next_pos = next_pos;
         next_next_pos.x += dir.x;
         next_next_pos.y += dir.y;
         
         if (next_pos.x < 0 || next_pos.y < 0 || next_pos.x >= side_size || next_pos.y >= side_size ||
            (next_next_pos.x >= 0 && next_next_pos.y >= 0 && next_next_pos.x < side_size && next_next_pos.y < side_size &&
            grid[next_next_pos.y][next_next_pos.x] != ' '))
         {
            int x_tmp = dir.x;
            if (direction == "clockwise")
            {
               dir.x = -dir.y;
               dir.y = x_tmp;
            }
            else
            { 
               dir.x = dir.y;
               dir.y = -x_tmp;
            }
            next_pos.x = pos.x + dir.x;
            next_pos.y = pos.y + dir.y;
            if (in_a_row == 2)
            {
               ++counter; 
            }
            if (counter == 2)
            {
               std::cout << grid << std::endl;
               return 0;
            }
            in_a_row = 0;
         }
         pos = std::move(next_pos);
      }
      sign = ((sign - 'A') - char_diff) + 'A';
      if (sign > 'Z' || sign < 'A')
      {
         std::cout << grid << std::endl;
         return 0;
      }
      size -= size_diff;
   }

   return 0;
}
