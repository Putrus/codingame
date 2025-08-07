#include <iostream>
#include <string>
#include <vector>

constexpr int ZONE_SIZE = 30;

int charToVal(char c)
{
   return (c == ' ') ? 0 : c - 'A' + 1;
}

int valToChar(int v)
{
   return (v == 0) ? ' ' : 'A' + v - 1;
}

int shortestDelta(char from, char to)
{
   int from_val = charToVal(from);
   int to_val = charToVal(to);

   int delta = (to_val - from_val + 27) % 27;
   if (delta > 13)
   {
      delta -= 27;
   }
   return delta;
}

int main()
{
   std::string magic_phrase;
   std::getline(std::cin, magic_phrase);

   std::string runes(ZONE_SIZE, ' ');

   std::string solution = "";
   int position = 0;
   
   for (int i = 0; i < magic_phrase.size(); ++i)
   {
      size_t sign_position = runes.find(magic_phrase[i]);
      if (sign_position != std::string::npos)
      {
         int best_signed_dist = 0;
         int min_abs_dist = ZONE_SIZE + 1;
         for (int j = 0; j < ZONE_SIZE; ++j)
         {
            if (runes[j] != magic_phrase[i])
            {
               continue;
            }
            int forward = (j - position + ZONE_SIZE) % ZONE_SIZE;
            int backward = forward - ZONE_SIZE;

            if (std::abs(forward) < min_abs_dist)
            {
               min_abs_dist = std::abs(forward);
               best_signed_dist = forward;
            }

            if (std::abs(backward) < min_abs_dist)
            {
               min_abs_dist = std::abs(backward);
               best_signed_dist = backward;
            }
         }

         for (int j = 0; j < min_abs_dist; ++j)
         {
            if (best_signed_dist < 0)
            {
               solution += "<";
               --position;
               if (position == -1)
               {
                  position = ZONE_SIZE - 1;
               }
            }
            else if (best_signed_dist > 0)
            {
               solution += ">";
               ++position;
               if (position == ZONE_SIZE)
               {
                  position = 0; 
               }
            }
         } 
      }
      else
      {
         solution += ">";
         ++position;
         if (position == ZONE_SIZE)
         {
            position = 0;
         }
         while (runes[position] != magic_phrase[i])
         {
            int delta = shortestDelta(runes[position], magic_phrase[i]);
            if (delta < 0)
            {
               solution += "-";
               if (runes[position] == ' ')
               {
                  runes[position] = 'Z';
               }
               else if (runes[position] == 'A')
               {
                  runes[position] = ' ';
               }
               else
               {
                  --runes[position];
               }
            }
            else if (delta >= 0)
            {
               solution += "+";
               if (runes[position] == ' ')
               {
                  runes[position] = 'A';
               }
               else if (runes[position] == 'Z')
               {
                  runes[position] = ' ';
               }
               else
               {
                  ++runes[position];
               }
            }
         }
      }
      solution += ".";
   }
   std::cout << solution << std::endl;
}