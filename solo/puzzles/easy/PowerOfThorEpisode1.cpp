#include <iostream>

int main()
{
    int light_x;
    int light_y;
    int tx;
    int ty;
    std::cin >> light_x >> light_y >> tx >> ty;
    std::cin.ignore();

    while (1) {
        int remaining_turns;
        std::cin >> remaining_turns;
        std::cin.ignore();
        
        if (light_y < ty)
        {
            std::cout << "N";
            --ty;
        }
        else if (light_y > ty)
        {
            std::cout << "S";
            ++ty;
        }

        if (light_x < tx)
        {
            std::cout << "W";
            --tx;
        }
        else if (light_x > tx)
        {
            std::cout << "E";
            ++tx;
        }
        std::cout << std::endl;
    }
}