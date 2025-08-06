#include <iostream>
#include <cmath>

int main()
{
    // game loop
    while (true)
    {
        int x;
        int y;
        int next_checkpoint_x; // x position of the next check point
        int next_checkpoint_y; // y position of the next check point
        int next_checkpoint_dist; // distance to the next checkpoint
        int next_checkpoint_angle; // angle between your pod orientation and the direction of the next checkpoint
        std::cin >> x >> y >> next_checkpoint_x >> next_checkpoint_y >> next_checkpoint_dist >> next_checkpoint_angle; std::cin.ignore();
        int opponent_x;
        int opponent_y;
        std::cin >> opponent_x >> opponent_y; std::cin.ignore();

        double dx = x - next_checkpoint_x;
        double dy = y - next_checkpoint_y;
        double distance_to_next_checkpoint = std::sqrt(dx * dx + dy * dy);
        int destination_x = next_checkpoint_x + dx / distance_to_next_checkpoint * 400.0;
        int destination_y = next_checkpoint_y + dy / distance_to_next_checkpoint * 400.0;
        std::string thrust = "100";
        if (next_checkpoint_angle > 90 || next_checkpoint_angle < -90)
        {
            thrust = "10";        }
        else if (next_checkpoint_angle > 45 || next_checkpoint_angle < -45)
        {
            thrust = "50";
        }
        else if (next_checkpoint_dist > 2000)
        {
            thrust = "BOOST";
        }

        std::cout << destination_x << " " << destination_y << " " << thrust << std::endl;
    }
}