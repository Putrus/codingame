#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> split(std::string s, const std::string& delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}

int main()
{
    std::string data;
    std::getline(std::cin, data);

    std::vector<std::string> splitted = split(data, ",");

    std::string name = splitted[0];
    std::string rarity = splitted[1];
    int longest = std::max(name.size() + 2, rarity.size());
    for (int i = 2; i < splitted.size(); ++i)
    {
        std::replace(splitted[i].begin(), splitted[i].end(), ':', ' ');
        if (splitted[i].size() > longest)
        {
            longest = splitted[i].size();
        }
    }

    if (rarity == "Common")
    {
        for (int i = 0; i < longest + 4; ++i)
        {
            std::cout << '#';
        }
        std::cout << std::endl;

        //name
        std::cout << '#';
        int diff = longest - name.size() - 2;
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << '-' << name << '-';
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << '#' << std::endl;

        //rarity
        std::cout << '#';
        diff = longest - rarity.size();
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << rarity;
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << '#' << std::endl;

        for (int i = 2; i < splitted.size(); ++i)
        {
            std::cout << "# " << splitted[i];

            for (int j = 0; j < longest - splitted[i].size() + 1; ++j)
            {
                std::cout << ' ';
            }
            std::cout << '#' << std::endl;
        }

        for (int i = 0; i < longest + 4; ++i)
        {
            std::cout << '#';
        }
        std::cout << std::endl;
    }
    else if (rarity == "Rare")
    {
        std::cout << '/';
        for (int i = 0; i < longest + 2; ++i)
        {
            std::cout << '#';
        }
        std::cout << '\\' << std::endl;

        //name
        std::cout << '#';
        int diff = longest - name.size() - 2;
        bool diff_odd = diff % 2 != 0;
        if (diff_odd)
        {
            ++diff;
        }
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << '-' << name << '-';
        if (diff_odd)
        {
            --diff;
        }
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << '#' << std::endl;

        //rarity
        std::cout << '#';
        diff = longest - rarity.size();
        diff_odd = diff % 2 != 0;
        if (diff_odd)
        {
            ++diff;
        }
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << rarity;
        if (diff_odd)
        {
            --diff;
        }
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << '#' << std::endl;

        for (int i = 2; i < splitted.size(); ++i)
        {
            std::cout << "# " << splitted[i];

            for (int j = 0; j < longest - splitted[i].size() + 1; ++j)
            {
                std::cout << ' ';
            }
            std::cout << '#' << std::endl;
        }

        std::cout << '\\';
        for (int i = 0; i < longest + 2; ++i)
        {
            std::cout << '#';
        }
        std::cout << '/' << std::endl;
    }
    else if (rarity == "Epic")
    {
        std::cout << '/';
        for (int i = 0; i < longest + 2; ++i)
        {
            std::cout << '-';
        }
        std::cout << '\\' << std::endl;

        //name
        std::cout << '|';
        int diff = longest - name.size() - 2;
        bool diff_odd = diff % 2 != 0;
        if (diff_odd)
        {
            ++diff;
        }
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << '-' << name << '-';
        if (diff_odd)
        {
            --diff;
        }
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << '|' << std::endl;

        //rarity
        std::cout << '|';
        diff = longest - rarity.size();
        diff_odd = diff % 2 != 0;
        if (diff_odd)
        {
            ++diff;
        }
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << rarity;
        if (diff_odd)
        {
            --diff;
        }
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << '|' << std::endl;

        for (int i = 2; i < splitted.size(); ++i)
        {
            std::cout << "| " << splitted[i];

            for (int j = 0; j < longest - splitted[i].size() + 1; ++j)
            {
                std::cout << ' ';
            }
            std::cout << '|' << std::endl;
        }

        std::cout << '\\';
        for (int i = 0; i < longest + 2; ++i)
        {
            std::cout << '_';
        }
        std::cout << '/' << std::endl;
    }
    else
    {
        std::cout << 'X';
        int minus = 1;
        if (longest % 2 == 0)
        {
            minus = 2;
        }
        for (int i = 0; i < (longest + 2) / 2 - minus; ++i)
        {
            std::cout << '-';
        }
        if (longest % 2 == 0)
        {
            std::cout << "\\__/";
        }
        else
        {
            std::cout << "\\_/";
        }
        for (int i = 0; i < (longest + 2) / 2 - minus; ++i)
        {
            std::cout << '-';
        }
        std::cout << 'X' << std::endl;

        //name
        std::cout << '[';
        int diff = longest - name.size() - 2;
        bool diff_odd = diff % 2 != 0;
        if (diff_odd)
        {
            ++diff;
        }
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << '-' << name << '-';
        if (diff_odd)
        {
            --diff;
        }
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << ']' << std::endl;

        //rarity
        std::cout << '|';
        diff = longest - rarity.size();
        diff_odd = diff % 2 != 0;
        if (diff_odd)
        {
            ++diff;
        }
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << rarity;
        if (diff_odd)
        {
            --diff;
        }
        for(int i = 0; i < diff / 2 + 1; ++i)
        {
            std::cout << ' ';
        }
        std::cout << '|' << std::endl;

        for (int i = 2; i < splitted.size(); ++i)
        {
            std::cout << "| " << splitted[i];

            for (int j = 0; j < longest - splitted[i].size() + 1; ++j)
            {
                std::cout << ' ';
            }
            std::cout << '|' << std::endl;
        }

        std::cout << 'X';
        for (int i = 0; i < longest + 2; ++i)
        {
            std::cout << '_';
        }
        std::cout << 'X' << std::endl;
    }
}