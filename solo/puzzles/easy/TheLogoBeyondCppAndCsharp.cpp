#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Logo
{
public:

private:
   void printHorizontal(std::ostream &os, int i, int y, bool top) const;

   friend std::istream& operator>>(std::istream& is, Logo& logo);
   friend std::ostream& operator<<(std::ostream& os, const Logo& logo);

   int size;
   int thickness;
   std::vector<std::string> pluses;
};

void Logo::printHorizontal(std::ostream& os, int i, int y, bool top) const
{
   for (int j = 0; j < pluses[i].size(); ++j)
   {
      char print_char = pluses[i][j];
      for (int x = 0; x < (size - thickness) / 2; ++x)
      {
         os << ' ';
      }

      if (top && y == 0 && (i - 1 < 0 || j >= pluses[i - 1].size() || pluses[i - 1][j] == ' '))
      {
         for (int x = 0; x < thickness; ++x)
         {
            os << print_char;
         }
      }
      else if (!top && y == (size - thickness) / 2 - 1 && (i + 1 >= pluses.size() || j >= pluses[i + 1].size() || pluses[i + 1][j] == ' '))
      {
         for (int x = 0; x < thickness; ++x)
         {
            os << print_char;
         }
      }
      else
      {
         os << print_char;
         for (int x = 0; x < thickness - 2; ++x)
         {
            os << ' ';
         }
         os << print_char;
      }

      if (j == pluses[i].size() - 1)
      {
         return;
      }

      for (int x = 0; x < (size - thickness) / 2; ++x)
      {
         os << ' ';
      }
   }
}

std::istream& operator>>(std::istream& is, Logo& logo)
{
   is >> logo.size; is.ignore();
   is >> logo.thickness; std::cin.ignore();
   int n;
   is >> n; is.ignore();
   for (int i = 0; i < n; ++i)
   {
      std::string pluses_line;
      std::getline(is, pluses_line);
      logo.pluses.push_back(pluses_line);
   }
   return is;
}

std::ostream& operator<<(std::ostream& os, const Logo& logo)
{
   for (int i = 0; i < logo.pluses.size(); ++i)
   {
      for (int y = 0; y < (logo.size - logo.thickness) / 2; ++y)
      {
         logo.printHorizontal(os, i, y, true);
         os << std::endl;
      }

      for (int y = 0; y < logo.thickness; ++y)
      {
         for (int j = 0; j < logo.pluses[i].size(); ++j)
         {
            char print_char = logo.pluses[i][j];
            if (y == 0 || y == logo.thickness - 1)
            {
               for (int x = 0; x < (logo.size - logo.thickness) / 2 + 1; ++x)
               {
                  os << print_char;
               }

               for (int x = 0; x < logo.thickness - 2; ++x)
               {
                  os << ' ';
               }

               for (int x = 0; x < (logo.size - logo.thickness) / 2 + 1; ++x)
               {
                  os << print_char;
               }
            }
            else
            {
               if (j - 1 < 0 || logo.pluses[i][j - 1] == ' ')
               {
                  os << print_char;
               }
               else
               {
                  os << ' ';
               }

               for (int x = 0; x < logo.size - 2; ++x)
               {
                  os << ' ';
               }

               if (j + 1 >= logo.pluses[i].size() || logo.pluses[i][j + 1] == ' ')
               {
                  os << print_char;
               }
               else
               {
                  os << ' ';
               }
            }
         }
         os << std::endl;
      }

      for (int y = 0; y < (logo.size - logo.thickness) / 2; ++y)
      {
         logo.printHorizontal(os, i, y, false);
         os << std::endl;
      }
   }
   return os;
}

int main()
{
   Logo logo;
   std::cin >> logo;
   std::cout << logo;
}