#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::string typed_keys;
    getline(std::cin, typed_keys);

    int cursor = 0;
    
    std::string computed_text;
    for (char key : typed_keys)
    {
        if (key == '-')
        {
            int delete_place = cursor - 1;
            if (delete_place >= 0 && delete_place < computed_text.size())
            {
                computed_text.erase(computed_text.begin() + delete_place);
                --cursor;
            }
        }
        else if (key == '<')
        {
            --cursor;
        }
        else if (key == '>')
        {
            ++cursor;
        }
        else
        {
            if (cursor == computed_text.size())
            {
                computed_text.push_back(key);
            }
            else
            {
                std::string computed_text_pre_substr = computed_text.substr(0, cursor);
                computed_text_pre_substr += key;
                std::string computed_text_post_substr = computed_text.substr(cursor);
                computed_text = computed_text_pre_substr + computed_text_post_substr;
            }
            ++cursor;
        }
        cursor = std::max(std::min(cursor, static_cast<int>(computed_text.size())), 0);
    }

    std::cout << computed_text << std::endl;
}