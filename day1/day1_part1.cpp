// Day1 Part 2
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>

int retrieveNumber(std::string_view line)
{
    int firstDigit  = -1;
    int secondDigit = -1;
    for(char c : line)
    {
        if (std::isdigit(c))
        {
            if (firstDigit == -1)
            {
                firstDigit = c - '0';
                secondDigit = firstDigit;
            }
            else
            {
                secondDigit = c - '0';
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

    int sum = 0;
    for (std::string line; std::getline(data, line);)
    {
        int number = retrieveNumber(line);
        sum += number;
        std::cout << "  " << number << "\n";
    }

    std::cout << "sum = " << sum << "\n";

    return EXIT_SUCCESS;
}
