#include <iostream>
#include <cmath>
#include <vector>

std::vector<double> getLineParameters(double x1, double y1, double x2, double y2)
{
   double a = (y2 - y1) / (x2 - x1);
   double b = y1 - a * x1;
   return { a, b };
}

int main()
{
   std::vector<std::pair<int,int>> checkpoint_list;
   std::vector<std::pair<int,int>> position_list;

   int checkpoint_index = 0;
   int frame_index = 0;
   int boost_used = 0;

   std::vector<double> line_parameters;
   std::vector<double> new_destination(2);

   while (true)
   {
      int x, y;
      int next_checkpoint_x, next_checkpoint_y;
      int next_checkpoint_distance, next_checkpoint_angle;

      std::cin >> x >> y >> next_checkpoint_x >> next_checkpoint_y >> next_checkpoint_distance >> next_checkpoint_angle;
      int opponent_x, opponent_y;

      std::cin >> opponent_x >> opponent_y;
      double checkpoint_distance = next_checkpoint_distance;
      double opponent_next_checkpoint_distance = std::sqrt(std::pow(opponent_x - next_checkpoint_x, 2) + std::pow(opponent_y - next_checkpoint_y, 2));
      double my_opponent_distance = std::sqrt(std::pow(opponent_x - x, 2) + std::pow(opponent_y - y, 2));

      if (checkpoint_list.empty())
      {
         checkpoint_list.push_back({next_checkpoint_x, next_checkpoint_y});
         checkpoint_index++;
      } 
      else if (checkpoint_list[checkpoint_index - 1].first != next_checkpoint_x ||
         checkpoint_list[checkpoint_index - 1].second != next_checkpoint_y)
      {
         checkpoint_list.push_back({next_checkpoint_x, next_checkpoint_y});
         checkpoint_index++;
      }

      if (checkpoint_index >= 2)
      {
         std::vector<double> new_line_parameters = getLineParameters(checkpoint_list[checkpoint_index - 1].first, checkpoint_list[checkpoint_index - 1].second,
            checkpoint_list[checkpoint_index - 2].first, checkpoint_list[checkpoint_index - 2].second);

         if (line_parameters != new_line_parameters)
         {
            line_parameters = new_line_parameters;

            int delta_x = checkpoint_list[checkpoint_index - 1].first - checkpoint_list[checkpoint_index - 2].first;
            int delta_y = checkpoint_list[checkpoint_index - 1].second - checkpoint_list[checkpoint_index - 2].second;

            double delta_r = std::sqrt(delta_x * delta_x + delta_y * delta_y);

            double new_delta_x = std::abs(600.0 * delta_x / delta_r);
            double new_delta_y = std::abs(600.0 * delta_y / delta_r);

            if (delta_x < 0 && delta_y < 0)
            {
               new_destination[0] = checkpoint_list[checkpoint_index - 1].first + new_delta_x;
               new_destination[1] = checkpoint_list[checkpoint_index - 1].second + new_delta_y;
            } 
            else if (delta_x < 0 && delta_y > 0)
            {
               new_destination[0] = checkpoint_list[checkpoint_index - 1].first + new_delta_x;
               new_destination[1] = checkpoint_list[checkpoint_index - 1].second - new_delta_y;
            } 
            else if (delta_x > 0 && delta_y > 0)
            {
               new_destination[0] = checkpoint_list[checkpoint_index - 1].first - new_delta_x;
               new_destination[1] = checkpoint_list[checkpoint_index - 1].second - new_delta_y;
            } 
            else if (delta_x > 0 && delta_y < 0)
            {
               new_destination[0] = checkpoint_list[checkpoint_index - 1].first - new_delta_x;
               new_destination[1] = checkpoint_list[checkpoint_index - 1].second + new_delta_y;
            }
         }
      }

      int thrust = 100;

      if (std::abs(next_checkpoint_angle) > 90)
      {
         thrust = 0;
      } 
      else if (next_checkpoint_distance < 1500)
      {
         thrust = 0;
      }

      position_list.push_back({ x, y });

      if (frame_index >= 1)
      {
         int dx = position_list[frame_index - 1].first - position_list[frame_index].first;
         int dy = position_list[frame_index - 1].second - position_list[frame_index].second;

         if (std::abs(dx) < 350 && std::abs(dy) < 350)
         {
            thrust = 100;
         }
      }

      if (boost_used == 0 &&
         opponent_next_checkpoint_distance < 600 &&
         checkpoint_distance > 600 &&
         checkpoint_distance < 1200) 
      {
         boost_used = 1;
         std::cout << opponent_x << " " << opponent_y << " BOOST\n";
      }
      else if (checkpoint_index >= 2)
      {
         std::cout << static_cast<int>(new_destination[0]) << " " << static_cast<int>(new_destination[1]) << " " << thrust << std::endl;;
      }
      else
      {
         std::cout << next_checkpoint_x << " " << next_checkpoint_y << " " << thrust << std::endl;
      }

      frame_index++;
   }

   return 0;
}
