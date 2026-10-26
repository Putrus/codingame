#include <algorithm>
#include <iostream>
#include <vector>

struct Coin
{
    int count;
    int value;
};

int main()
{
    int value_to_reach;
    std::cin >> value_to_reach; std::cin.ignore();
    int n;
    std::cin >> n; std::cin.ignore();
    std::vector<Coin> coins;
    for (int i = 0; i < n; i++)
    {
        int count;
        std::cin >> count; std::cin.ignore();
        coins.push_back({ count, 0 });
    }

    for (int i = 0; i < n; i++)
    {
        int value;
        std::cin >> value; std::cin.ignore();
        coins[i].value = value;
    }

    std::sort(coins.begin(), coins.end(), [](const Coin& lhs, const Coin& rhs)
        {
            return lhs.value < rhs.value;
        });

    int value_sum = 0;
    int i = 0;
    int result = 0;
    while (i < coins.size() && value_sum < value_to_reach)
    {
        if (coins[i].count == 0)
        {
            ++i;
        }
        else
        {
            value_sum += coins[i].value;
            --coins[i].count;
            ++result;
        }
    }

    if (value_sum < value_to_reach)
    {
        result = -1;
    }

    std::cout << result << std::endl;
}