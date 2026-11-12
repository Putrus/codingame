#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int main()
{
   int n;
   std::cin >> n; std::cin.ignore();
   std::vector<int> time_stamps;
   int timer_stop_time = 0;
   for (int p = 0; p < n; p++)
   {
      std::string time_stamp;
      getline(std::cin, time_stamp);
      int t = stoi(time_stamp.substr(0, time_stamp.find(':'))) * 60 +
         stoi(time_stamp.substr(time_stamp.find(':') + 1));

      if (p == 6)
      {
         timer_stop_time = t;
         break;
      }
      if (t < timer_stop_time)
         break;
      int seconds = 256 / (1 << p);
      timer_stop_time = std::max(0, t - seconds);
   }
   int seconds = timer_stop_time % 60;
   if (n == 0)
   {
      std::cout << "NO GAME" << std::endl;
      return 0;
   }
   std::cout << timer_stop_time / 60 << ":" << (seconds != 0 ? seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds) : "00") << std::endl;
}
