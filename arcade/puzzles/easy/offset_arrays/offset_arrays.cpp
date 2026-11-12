#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

class OffsetArray
{
public:
   OffsetArray(const std::string& str)
   {
      int bracket_pos = str.find('[');
      begin_index = stoi(str.substr(bracket_pos + 1, str.find('.') - bracket_pos));
      std::stringstream ss(str.substr(str.find('=') + 2));
      int element = 0;
      while (ss >> element)
      {
         elements.push_back(element);
      }
   }

   int& operator[](int idx)
   {
      return elements[idx - begin_index];
   }

   int operator[](int idx) const
   {
      return elements[idx - begin_index];
   }

   friend std::ostream& operator<<(std::ostream& os, const OffsetArray& array);

private:
   int begin_index = 0;
   std::vector<int> elements;
};

std::ostream& operator<<(std::ostream& os, const OffsetArray& array)
{
   os << "[";
   for (int i = 0; i < array.elements.size() - 1; ++i)
   {
      os << array.elements[i] << ", ";
   }
   os << array.elements.back() << "]";
   return os;
}

int main()
{
   int n;
   std::cin >> n; std::cin.ignore();
   std::map<std::string, OffsetArray> arrays;
   for (int i = 0; i < n; i++)
   {
      std::string assignment;
      getline(std::cin, assignment);
      OffsetArray a(assignment);
      arrays.insert_or_assign(assignment.substr(0, assignment.find('[')), a);
   }
   std::string x;
   getline(std::cin, x);
   size_t open_bracket_pos = x.find_last_of('[');
   while (open_bracket_pos != std::string::npos)
   {
      int previous_open_bracket_pos = open_bracket_pos - 1;
      size_t close_bracket_pos = x.find(']');
      for (; previous_open_bracket_pos >= 0 ; --previous_open_bracket_pos)
      {
         if (x[previous_open_bracket_pos] == '[')
         {
            break;
         }
      }
      std::string array_name = x.substr(previous_open_bracket_pos + 1, open_bracket_pos - previous_open_bracket_pos - 1);
      int index = stoi(x.substr(open_bracket_pos + 1, close_bracket_pos - open_bracket_pos - 1));
      x.replace(previous_open_bracket_pos + 1,
        close_bracket_pos - previous_open_bracket_pos, std::to_string(arrays.at(array_name)[index]));
      open_bracket_pos = x.find_last_of('[');
   }
   
   std::cout << x << std::endl;
}
