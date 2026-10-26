#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
   int l;
   int s;
   int n;
   std::cin >> l >> s >> n; std::cin.ignore();
   std::string code;
   std::vector<int> inputs;
   int input_position = 0;
   for (int i = 0; i < l; i++)
   {
      std::string r;
      std::getline(std::cin, r);
      r.erase(std::remove_if(r.begin(), r.end(), [](char c) {
         return !(c == '>' || c == '<' || c == '+' || c == '-' || c == '.' || c == ',' || c == '[' || c == ']');}), r.end());
      code += r;
   }
   std::vector<int> memory(s, 0);
   int pointer_position = 0;
   for (int i = 0; i < n; i++)
   {
      int c;
      std::cin >> c; std::cin.ignore();
      inputs.push_back(c);
   }

   std::string output = "";
   for (int i = 0; i < code.size(); ++i)
   {
      if (code[i] == '>')
      {
         ++pointer_position;
      }
      else if (code[i] == '<')
      {
         --pointer_position;
      }
      else if (code[i] == '+')
      {
         ++memory[pointer_position];
      }
      else if (code[i] == '-')
      {
         --memory[pointer_position];
      }
      else if (code[i] == '.')
      {
         output += (char)(memory[pointer_position]);
      }
      else if (code[i] == ',')
      {
         memory[pointer_position] = inputs[input_position++];
      }
      else if (code[i] == '[')
      {
         int left = 1;
         int right = 0;
         int new_i = 0;
         for (int j = i + 1; j < code.size(); ++j)
         {
            if (code[j] == '[')
            {
               ++left;
            }
            else if (code[j] == ']')
            {
               ++right;
            }
            if (right == left)
            {
               new_i = j;
               break;
            }
         }

         if (right != left)
         {
            std::cout << "SYNTAX ERROR" << std::endl;
            return 0;
         }

         if (memory[pointer_position] != 0)
         {
            continue;
         }

         i = new_i;
      }
      else if (code[i] == ']')
      {
         int left = 0;
         int right = 1;
         int new_i = 0;
         for (int j = i - 1; j >= 0; --j)
         {
            if (code[j] == '[')
            {
               ++left;
            }
            else if (code[j] == ']')
            {
               ++right;
            }
            if (right == left)
            {
               new_i= j;
               break;
            }
         }

         if (right != left)
         {
            std::cout << "SYNTAX ERROR" << std::endl;
            return 0;
         }

         if (memory[pointer_position] == 0)
         {
            continue;
         }

         i = new_i;
      }
      else
      {
         std::cout << "SYNTAX ERROR" << std::endl;
         return 0;
      }

      if (pointer_position < 0 || pointer_position >= memory.size())
      {
         std::cout << "POINTER OUT OF BOUNDS" << std::endl;
         return 0;
      }

      if (memory[pointer_position] < 0 || memory[pointer_position] > 255)
      {
         std::cout << "INCORRECT VALUE" << std::endl;
         return 0;
      }
   }

   std::cout << output << std::endl;
}