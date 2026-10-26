#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <stack>
#include <iomanip>

struct Distribution
{
   Distribution() = default;
   Distribution(int val)
   {
      outcomes[val] = 1.0;
   }

   Distribution applyOperator(const Distribution& other, char op) const
   {
      Distribution result;
      for (const auto& [a, pa] : outcomes)
      {
         for (const auto& [b, pb] : other.outcomes)
         {
            int r = 0;
            switch (op)
            {
            case '+':
               r = a + b;
               break;
            case '-':
               r = a - b;
               break;
            case '*':
               r = a * b;
               break;
            case '>':
               r = a > b;
               break;
            }
            result.outcomes[r] += pa * pb;
         }
      }
      return result;
   }

   std::map<int, double> outcomes;
};

Distribution die(int sides)
{
   Distribution d;
   for (int i = 1; i <= sides; ++i)
   {
      d.outcomes[i] = 1.0 / sides;
   }
   return d;
}

int precedence(const std::string& op)
{
   if (op == "*")
   {
      return 3;
   }
   else if (op == "+" || op == "-")
   {
      return 2;
   }
   else if (op == ">")
   {
      return 1;
   }
   return 0;
}

std::vector<std::string> reversePolishNotation(const std::string& expr)
{
   std::vector<std::string> reverse_polish_notation;
   std::stack<std::string> operators;

   int i = 0;
   while (i < expr.size())
   {
      if (isdigit(expr[i]) || expr[i] == 'd')
      {
         int j = i;
         while (j < expr.size() && (isdigit(expr[j]) || expr[j] == 'd'))
         {
            ++j;
         }
         reverse_polish_notation.push_back(expr.substr(i, j - i));
         i = j;
      }
      else if (expr[i] == '(')
      {
         operators.push(std::string(1, expr[i]));
         ++i;
      }
      else if (expr[i] == ')')
      {
         while (!operators.empty() && operators.top() != "(")
         {
            reverse_polish_notation.push_back(operators.top());
            operators.pop();
         }
         if (!operators.empty())
         {
            operators.pop();
         }
         ++i;
      }
      else
      {
         std::string op(1, expr[i]);
         while (!operators.empty() && precedence(operators.top()) >= precedence(op))
         {
            reverse_polish_notation.push_back(operators.top());
            operators.pop();
         }
         operators.push(op);
         ++i;
      }
   }
   while (!operators.empty())
   {
      reverse_polish_notation.push_back(operators.top());
      operators.pop();
   }
   return reverse_polish_notation;
}

Distribution evaluate(const std::vector<std::string>& rpn)
{
   std::stack<Distribution> stack;
   for (const std::string& token : rpn)
   {
      if (token.empty())
      {
         continue;
      }

      if (isdigit(token[0]))
      {
         stack.push(Distribution(std::stoi(token)));
      }
      else if (token[0] == 'd')
      {
         stack.push(die(std::stoi(token.substr(1))));
      }
      else
      {
         Distribution b = stack.top();
         stack.pop();
         Distribution a = stack.top();
         stack.pop();
         stack.push(a.applyOperator(b, token[0]));
      }
   }
   return stack.top();
}

int main()
{
   std::string expr;
   std::getline(std::cin, expr);

   std::map<int, int> results;

   std::vector<std::string> rpn = reversePolishNotation(expr);

   Distribution result = evaluate(rpn);

   std::vector<std::pair<int, double>> output(result.outcomes.begin(), result.outcomes.end());
   std::sort(output.begin(), output.end());

   for (const auto& [value, probability] : output)
   {
      std::cout << value << " " << std::fixed << std::setprecision(2) << probability * 100 << std::endl;
   }
}