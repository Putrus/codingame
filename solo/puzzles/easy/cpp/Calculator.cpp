#include <iostream>
#include <iomanip>

std::string trimTrailingZeros(std::string str)
{
    size_t dotPos = str.find('.');
    if (dotPos == std::string::npos)
    {
        return str;
    }

    size_t end = str.size() - 1;
    while (end > dotPos && str[end] == '0')
    {
        --end;
    }

    if (end == dotPos)
    {
        --end;
    }
    return str.substr(0, end + 1);
}

std::string roundTo3DecimalPlaces(double value)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3) << value;

    return oss.str();
}

int main()
{
    int n;
    std::cin >> n;
    std::cin.ignore();
    bool first = true;
    bool equation_key = false;
    std::string first_number;
    std::string second_number;
    std::string operation;
    for (int i = 0; i < n; i++)
    {
        std::string key;
        getline(std::cin, key);
        if (key == "AC")
        {
            first = true;
            first_number.clear();
            second_number.clear();
            operation.clear();
            std::cout << 0 << std::endl;
        }
        else if (key[0] >= '0' && key[0] <= '9')
        {
            if (equation_key)
            {
                first = true;
                first_number.clear();
                second_number.clear();
                operation.clear();
                equation_key = false;
            }
            if (first)
            {
                first_number += key;
                std::cout << first_number << std::endl; 
            }
            else
            {
                second_number += key;
                std::cout << second_number << std::endl;
            }
        }
        else
        {
            if (!second_number.empty())
            {
                if (equation_key && key != "=")
                {
                    std::cout << trimTrailingZeros(first_number) << std::endl;
                    second_number.clear();
                    operation = key;
                    equation_key = false;
                    continue;    
                }
                if (operation == "-")
                {
                    first_number = std::to_string(std::stod(first_number) - std::stod(second_number));
                }
                else if (operation == "+")
                {
                   first_number = std::to_string(std::stod(first_number) + std::stod(second_number)); 
                }
                else if (operation == "x")
                {
                   first_number = std::to_string(std::stod(first_number) * std::stod(second_number)); 
                }
                else
                {
                    first_number = roundTo3DecimalPlaces(std::stod(first_number) / std::stod(second_number)); 
                }

                std::cout << trimTrailingZeros(first_number) << std::endl;
            }
            else
            {
                first = false;
                std::cout << trimTrailingZeros(first_number) << std::endl;
            }

            if (key != "=")
            {
                second_number.clear();
                operation = key;
            }
            else
            {
                equation_key = true;
            }
        }
    }
}