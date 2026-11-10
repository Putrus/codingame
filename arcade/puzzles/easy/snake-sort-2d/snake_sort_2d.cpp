#include <algorithm>
#include <iostream>
#include <vector>

constexpr int ROWS = 100;
constexpr int COLUMNS = 100;

int main()
{
   int n;
   std::cin >> n; std::cin.ignore();
   std::vector<std::string> array(ROWS, std::string(COLUMNS, '-'));
   for (int i = 0; i < n; i++)
   {
      std::string name;
      int r;
      int c;
      std::cin >> name >> r >> c; std::cin.ignore();
      array[r][c] = name[0];
      
   }

   int j = 0;
   std::string result;
   for (int i = 0; i < ROWS; ++i)
   {
      int empty_cells = std::count(array[i].begin(), array[i].end(), '-');
      if (empty_cells == COLUMNS)
         continue;

      if (j == 0)
      {
         for (; j < COLUMNS; ++j)
         {
            if (array[i][j] != '-')
            {
               result += array[i][j];
               result += ",";
            }
         }
         j = COLUMNS - 1;
      }
      else
      {
         for (; j >= 0; --j)
         {
            
            if (array[i][j] != '-')
            {
               result += array[i][j];
               result += ",";
            }
         }
         j = 0;
      }
   }
   std::cout << result.substr(0, result.size() - 1) << std::endl;
}
