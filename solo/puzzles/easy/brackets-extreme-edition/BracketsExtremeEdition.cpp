#include <iostream>
#include <string>
#include <stack>
#include <map>

int main()
{
   std::string expression;
   std::cin >> expression; std::cin.ignore();

   std::stack<char> stack;
   std::map<char, char> pairs = { { '{', '}' }, { '(', ')' }, { '[', ']' } }; 

   for (char bracket : expression)
   {
      if (pairs.find(bracket) != pairs.end())
      {
         stack.push(bracket);
      }
      else if (bracket == '}' || bracket == ')' || bracket == ']')
      {
         if (stack.empty())
         {
            std::cout << "false" << std::endl;
            return 0;
         }

         char open_bracket = stack.top();
         stack.pop();
         std::cerr << "open: " << open_bracket << " close: " << bracket << std::endl;
         if (bracket != pairs[open_bracket])
         {
            std::cout << "false" << std::endl;
            return 0;
         }
      }
   }

   if (stack.empty())
   {
      std::cout << "true" << std::endl;
   }
   else
   {
      std::cout << "false" << std::endl;
   }
   return 0;
}