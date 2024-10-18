#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

void checkSeries(const std::string& series, int& available_cards, int& available_cards_under, int bust_threshold)
{
   
   if (std::find_if(series.begin(), series.end(), [](char c)
      {
         return !((c >= '2' && c <= '9') || c == 'K' || c == 'Q' || c == 'J' || c == 'A' || c == 'T');
      }) != series.end())
   {
      return;
   }
   for (char card : series)
   {
      if (card >= '2' && card <= '9')
      {
         --available_cards;
         if (card - '0' < bust_threshold)
         {
            --available_cards_under;
         }
      }
      else if (card == 'A')
      {
         --available_cards;
         --available_cards_under;
      }
      else
      {
         --available_cards;
      }
   }
}

int main()
{
   std::string stream_of_consciousness;
   getline(std::cin, stream_of_consciousness);
   int bust_threshold;
   std::cin >> bust_threshold; std::cin.ignore();

   int available_cards = 52;
   int available_cards_under = (bust_threshold - 1) * 4;

   size_t dot_pos = stream_of_consciousness.find('.');
   while (dot_pos != std::string::npos)
   {
      std::string series = stream_of_consciousness.substr(0, dot_pos);
      stream_of_consciousness = stream_of_consciousness.substr(dot_pos + 1);
      dot_pos = stream_of_consciousness.find('.');

      checkSeries(series, available_cards, available_cards_under, bust_threshold);
   }

   checkSeries(stream_of_consciousness, available_cards, available_cards_under, bust_threshold);
   std::cout << static_cast<int>(std::round((available_cards_under * 100.0) / static_cast<double>(available_cards))) << '%' << std::endl;
}