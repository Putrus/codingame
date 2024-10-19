   #include <iostream>
   #include <string>
   #include <vector>
   #include <algorithm>
   #include <map>
   #include <iomanip>
   #include <cmath>

void toUpper(std::string& str)
{
   for (auto& c : str)
   {
      c = std::toupper(c);
   }
}

void printRow(double lower, double higher)
{
   int lower_percentage = static_cast<int>(std::round(lower));
   int higher_percentage = static_cast<int>(std::round(higher));
   std::cout << "  +";
   for (int i = 0; i < lower_percentage; ++i)
   {
      std::cout << '-';
   }
   int difference = higher_percentage - lower_percentage;
   
   int difference_iteration = difference;
   if (lower_percentage >= 1)
   {
      std::cout << '+';
      --difference_iteration;
   }

   for (int i = 0; i < difference_iteration; ++i)
   {
      std::cout << '-';
   }

   if (difference >= 1)
   {
      std::cout << '+';
   }

   std::cout << std::endl;
}

int main()
   {
   std::string s;
   std::getline(std::cin, s);

   toUpper(s);

   double all = 0.0;
   std::map<char, double> letters;
   for (char c = 'A'; c <= 'Z'; ++c)
   {
      letters.insert({c, 0.0});
   }

   for (char c : s)
   {
      if (c >= 'A' && c <= 'Z')
      {
         ++letters[c];
         ++all;
      }
   }

   std::cout << std::fixed << std::setprecision(2);
   double last_letter_percentage = 0.0;
   double percentage = -1.0;
   for (const auto& letter : letters)
   {
      percentage = letter.second * 100.0 / all;
      printRow(std::min(percentage, last_letter_percentage), std::max(percentage, last_letter_percentage));
      last_letter_percentage = percentage;
      std::cout << letter.first << " |";
      int int_percentage = static_cast<int>(std::round(percentage));
      for (int i = 0; i < int_percentage; ++i)
      {
         std::cout << ' ';
      }
      if (int_percentage >= 1)
      {
         std::cout << '|';
      }
      std::cout << percentage << '%' << std::endl;
   }

   printRow(0, percentage);
}