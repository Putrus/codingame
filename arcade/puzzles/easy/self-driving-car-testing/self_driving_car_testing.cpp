#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

int main()
{
   int n;
   std::cin >> n; std::cin.ignore();
   std::string xthen_commands;
   getline(std::cin, xthen_commands);
   std::stringstream ss(xthen_commands);

   std::string command;
   std::vector<std::string> commands;
   while (std::getline(ss, command, ';'))
   {
      commands.push_back(command);
   }

   int pos_x = stoi(commands[0]) - 1;
   int pos_y = 0;

   std::vector<std::string> road;
   for (int i = 0; i < n; i++)
   {
      std::string rthen_roadpattern;
      getline(std::cin, rthen_roadpattern);
      size_t semicolon_pos = rthen_roadpattern.find(';');
      int rows = stoi(rthen_roadpattern.substr(0, semicolon_pos));
      std::string row = rthen_roadpattern.substr(semicolon_pos + 1, rthen_roadpattern.size() - semicolon_pos);
      for (int j = 0; j < rows; ++j)
      {
         road.push_back(row);
      }
   }

   for (int i = 1; i < commands.size(); ++i)
   {
      int len = stoi(commands[i]);
      char dir = commands[i].back();
      for (int j = 0; j < len; ++j)
      {
         if (dir == 'R')
         {
            ++pos_x;
         }
         else if (dir == 'L')
         {
            --pos_x;
         }

         road[pos_y][pos_x] = '#';
         std::cout << road[pos_y] << std::endl;
         ++pos_y;
      }
   }
}
