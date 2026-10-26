#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

int main()
{
   std::map<std::string, std::string> signals;
   int n;
   std::cin >> n; std::cin.ignore();
   int m;
   std::cin >> m; std::cin.ignore();
   for (int i = 0; i < n; i++)
   {
      std::string input_name;
      std::string input_signal;
      std::cin >> input_name >> input_signal; std::cin.ignore();
      signals.insert({input_name, input_signal});
   }
   for (int i = 0; i < m; i++)
   {
      std::string output_name;
      std::string type;
      std::string input_name_1;
      std::string input_name_2;
      std::cin >> output_name >> type >> input_name_1 >> input_name_2; std::cin.ignore();
      std::cout << output_name << " ";
      if (type == "AND")
      {
         for(size_t i = 0; i < signals[input_name_1].size(); ++i)
         {
               if (signals[input_name_1][i] == '-' && signals[input_name_2][i] == '-')
               {
                  std::cout << '-';
               }
               else
               {
                  std::cout << '_';
               }
         }
      }
      else if (type == "OR")
      {
         for(size_t i = 0; i < signals[input_name_1].size(); ++i)
         {
               if (signals[input_name_1][i] == '-' || signals[input_name_2][i] == '-')
               {
                  std::cout << '-';
               }
               else
               {
                  std::cout << '_';
               }
         }
      }
      else if (type == "XOR")
      {
         for(size_t i = 0; i < signals[input_name_1].size(); ++i)
         {
               if (signals[input_name_1][i] != signals[input_name_2][i])
               {
                  std::cout << '-';
               }
               else
               {
                  std::cout << '_';
               }
         }
      }
      else if (type == "NAND")
      {
         for(size_t i = 0; i < signals[input_name_1].size(); ++i)
         {
               if (signals[input_name_1][i] == '-' && signals[input_name_2][i] == '-')
               {
                  std::cout << '_';
               }
               else
               {
                  std::cout << '-';
               }
         }
      }
      else if (type == "NOR")
      {
         for(size_t i = 0; i < signals[input_name_1].size(); ++i)
         {
               if (signals[input_name_1][i] == '-' || signals[input_name_2][i] == '-')
               {
                  std::cout << '_';
               }
               else
               {
                  std::cout << '-';
               }
         }
      }
      else
      {
         for(size_t i = 0; i < signals[input_name_1].size(); ++i)
         {
               if (signals[input_name_1][i] != signals[input_name_2][i])
               {
                  std::cout << '_';
               }
               else
               {
                  std::cout << '-';
               }
         }
      }

      std::cout << std::endl;
   }
}