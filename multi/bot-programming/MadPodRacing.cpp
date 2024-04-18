#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    // game loop
    while (1)
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

        if (next_checkpoint_angle > 90 || next_checkpoint_angle < -90)
        {
            std::cout << next_checkpoint_x << " " << next_checkpoint_y << " 0" << std::endl;
        }
        else if (next_checkpoint_dist > 2000)
        {
            std::cout << next_checkpoint_x << " " << next_checkpoint_y << " BOOST" << std::endl;
        }
        else
        {
            std::cout << next_checkpoint_x << " " << next_checkpoint_y << " 100" << std::endl;
        }
    }
}