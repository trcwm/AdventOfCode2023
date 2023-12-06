// Day1 Part 2
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>
#include <array>

int retrieveNumber(std::string_view line)
{
    constexpr std::array<const char*, 9> digitTxt = 
    {
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    int firstDigit  = -1;
    int secondDigit = -1;

    int idx = 0;
    while(idx < line.size())
    {
        int currentDigit = -1;

        if (std::isdigit(line.at(idx)))
        {
            char c = line.at(idx);
            currentDigit = c - '0';
            idx++;
        }
        else
        {
            auto remainder = line.substr(idx, line.size() - idx);

            for(int digitIdx=0; digitIdx < digitTxt.size(); digitIdx++)
            {
                auto digit = std::string_view(digitTxt.at(digitIdx));
                if (remainder.compare(0, digit.size(), digit) == 0)
                {
                    currentDigit = digitIdx+1;
                    break;
                }                
            }

            // apparently digits defined by text
            // are allowed to overlap! :-(
            idx += 1;
        }

        if (currentDigit != -1)
        {
            if (firstDigit == -1)
            {
                firstDigit = currentDigit;
                secondDigit = currentDigit;
            }
            else
            {
                secondDigit = currentDigit;
            }
        }
    }
    
    return firstDigit*10 + secondDigit;
}

int main(const int argc, const char *argv[])
{
    std::ifstream data("data.txt");

    if (!data.is_open())
    {
        std::cerr << "Cannot open data.txt!\n";
        return EXIT_FAILURE;
    }

    int lineNum = 1;
    int sum = 0;
    for (std::string line; std::getline(data, line);)
    {
        int number = retrieveNumber(line);
        sum += number;
        std::cout << "  line " << lineNum << " " << number << "\n";
        lineNum++;
    }

    std::cout << "sum = " << sum << "\n";

    return EXIT_SUCCESS;
}
