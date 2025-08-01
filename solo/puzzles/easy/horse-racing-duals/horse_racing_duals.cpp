#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int n;
    std::cin >> n; std::cin.ignore();
    std::vector<int> v;
    for (int i = 0; i < n; i++) {
        int pi;
        std::cin >> pi; std::cin.ignore();
        v.push_back(pi);
    }
    std::sort(v.begin(), v.end());
    
    int min = 10000000;
    for(int i = 1; i < v.size(); ++i)
    {
        int diff = std::abs(v[i] - v[i - 1]);
        if (diff < min)
        {
            min = diff;
        }
    }
    std::cout << min << std::endl;
}